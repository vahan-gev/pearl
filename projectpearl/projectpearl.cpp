#include <iostream>
#include <unordered_set>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Pearl.h"
#include "Scene.h"
#include "Cube.h"

// Custom hash and equality functions for Cube pointers
struct CubeHash {
    std::size_t operator()(const Cube* cube) const {
        const glm::vec3& pos = cube->position;
        return std::hash<float>()(pos.x) ^ std::hash<float>()(pos.y) ^ std::hash<float>()(pos.z);
    }
};

struct CubeEqual {
    bool operator()(const Cube* lhs, const Cube* rhs) const {
        return lhs->position == rhs->position;
    }
};

// Unordered set to store unique Cube pointers
std::unordered_set<Cube*, CubeHash, CubeEqual> placedBlocks;

Camera* camera;
Scene* scene;
Cube* placeholder;
bool placeHolderExists = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
const char* texture_path = "textures/wood.png";
int texture_type = 0;
bool isMousePressed = false;
double lastClickTime = 0.0;
float placementDistance = 3.0f; // Distance in units to place the block in front

glm::vec3 calculateDirection(float yaw, float pitch) {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::normalize(direction);
}

void removeCubeAtPosition(const glm::vec3& position) {
    // Find the cube with the specified position
    for (auto it = placedBlocks.begin(); it != placedBlocks.end(); ++it) {
        Cube* cube = *it;
        if (cube->position == position) {
            // Remove the cube from the set
            placedBlocks.erase(it);

            // Also remove the cube from the scene
            scene->remove(cube->id);

            // Free the memory if necessary
            delete cube;

            // Exit the function since we found and removed the cube
            return;
        }
    }
    // If no cube was found, you could print a message or handle this case
    std::cout << "No cube found at position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
}

void processInput(GLFWwindow* window) {
    double currentTime = glfwGetTime();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera->Position.y += 5.0f * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera->Position.y -= 5.0f * deltaTime;
    }
    // This is some terrible code, but it works for now
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        texture_path = "textures/wood.png";
        texture_type = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        texture_path = "textures/glass.png";
        texture_type = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        texture_path = "textures/diamond_ore.png";
        texture_type = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        texture_path = "textures/cobblestone.png";
        texture_type = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        texture_path = "textures/diamond.png";
        texture_type = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS) {
        texture_path = "textures/deepslate_bricks.png";
        texture_type = 0;
    }
        
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
        texture_path = "textures/grass_block.png";
	    texture_type = 1;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        if (currentTime - lastClickTime > 0.2) {
            lastClickTime = currentTime;
            if (placeHolderExists) {
                placeholder->visible = false;
            }
            else {
                placeholder->visible = true;
            }
            placeHolderExists = !placeHolderExists;
        }
    }   
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (!isMousePressed && (currentTime - lastClickTime) > 0.2) {
            isMousePressed = true;
            lastClickTime = currentTime;

            glm::vec3 direction = calculateDirection(camera->Yaw, camera->Pitch);
            glm::vec3 targetPosition = camera->Position + direction * placementDistance;

            // Snap the target position to the nearest grid point
            glm::vec3 snappedPosition;
            snappedPosition.x = round(targetPosition.x);
            snappedPosition.y = round(targetPosition.y);
            snappedPosition.z = round(targetPosition.z);

            // Check if a cube at the snapped position already exists
            Cube* existingBlock = nullptr;
            for (Cube* cube : placedBlocks) {
                if (cube->position == snappedPosition) {
                    existingBlock = cube;
                    break;
                }
            }

            if (!existingBlock) {
                Cube* newBlock = new Cube(texture_path, texture_type);
                newBlock->position = snappedPosition;
                scene->add(newBlock);
                placedBlocks.insert(newBlock);
            }
        }
    }
    else {
        isMousePressed = false;
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (!isMousePressed && (currentTime - lastClickTime) > 0.2) {
            isMousePressed = true;
            lastClickTime = currentTime;

            glm::vec3 direction = calculateDirection(camera->Yaw, camera->Pitch);
            glm::vec3 targetPosition = camera->Position + direction * placementDistance;

            // Snap the target position to the nearest grid point
            glm::vec3 snappedPosition;
            snappedPosition.x = round(targetPosition.x);
            snappedPosition.y = round(targetPosition.y);
            snappedPosition.z = round(targetPosition.z);

            // Check if a cube at the snapped position already exists
            Cube* existingBlock = nullptr;
            for (Cube* cube : placedBlocks) {
                if (cube->position == snappedPosition) {
                    existingBlock = cube;
                    break;
                }
            }

            if (existingBlock) {
                removeCubeAtPosition(existingBlock->position);
            }
        }
    }
    else {
        isMousePressed = false;
    }
}

int main() {
    camera = new Camera(glm::vec3(0.0f, 0.0f, -3.0f));
    Pearl pearl(camera);
    pearl.initialize();

    scene = new Scene();
    placeholder = new Cube("textures/placeholder.png", 0);
    scene->add(placeholder);
    placeHolderExists = true;

    const int grid_size = 16;
    for (int x = 0; x < grid_size; ++x) {
        for (int z = 0; z < grid_size; ++z) {
            Cube* grass_block = new Cube("textures/grass_block.png", 1);
            grass_block->position.x = static_cast<float>(x);
            grass_block->position.z = static_cast<float>(z);
            scene->add(grass_block);
            placedBlocks.insert(grass_block);
        }
    }

    glm::vec3 placeholderPosition;
    while (!pearl.shouldClose()) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        std::cout << "FPS: " << 1.0f / deltaTime << std::endl;
        glm::vec3 direction = calculateDirection(camera->Yaw, camera->Pitch);
        glm::vec3 targetPosition = camera->Position + direction * placementDistance;
        placeholderPosition.x = round(targetPosition.x);
        placeholderPosition.y = round(targetPosition.y);
        placeholderPosition.z = round(targetPosition.z);
        placeholder->position = placeholderPosition;
        processInput(pearl.window);
        pearl.draw(scene);
    }

    delete scene;
    return 0;
}
