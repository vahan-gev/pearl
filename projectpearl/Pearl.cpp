#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_s.h"
#include <iostream>
#include "Pearl.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Cube.h"
// settings
float SCR_WIDTH = 1600.0f;
float SCR_HEIGHT = 1000.0f;
unsigned int VAO, VBO, EBO, texture;
Shader* shaderProgram;
GLFWwindow* Pearl::window = nullptr;

// Static member initialization
Camera* Pearl::s_camera = nullptr;
bool Pearl::s_firstMouse = true;
float Pearl::s_lastX = SCR_WIDTH / 2.0f;
float Pearl::s_lastY = SCR_HEIGHT / 2.0f;

Pearl::Pearl(Camera* cam) : camera(cam) {
    s_camera = cam;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Pearl::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (s_firstMouse)
    {
        s_lastX = xpos;
        s_lastY = ypos;
        s_firstMouse = false;
    }

    float xoffset = xpos - s_lastX;
    float yoffset = s_lastY - ypos; // reversed since y-coordinates go from bottom to top

    s_lastX = xpos;
    s_lastY = ypos;

    s_camera->ProcessMouseMovement(xoffset, yoffset);
    glm::vec3 snappedPosition;
    

}

void Pearl::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    s_camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

int Pearl::initialize() {
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    Pearl::window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project Pearl", NULL, NULL);
    //Pearl::window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project Pearl", glfwGetPrimaryMonitor(), NULL); // Replace with this when using fullscreen
    if (Pearl::window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(Pearl::window);
    glfwSetFramebufferSizeCallback(Pearl::window, framebuffer_size_callback);
    glfwSetCursorPosCallback(Pearl::window, Pearl::mouse_callback);
    glfwSetScrollCallback(Pearl::window, Pearl::scroll_callback);

    glfwSetInputMode(Pearl::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(Pearl::window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
    glfwSwapInterval(0); // VSYNC OFF
    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    shaderProgram = new Shader("vertexshader.vs", "fragmentshader.fs");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    return 0;
}

void Pearl::draw(Scene* scene) {

    // render
    glClearColor(232.0f / 255.0f, 207.0f / 255.0f, 166.0f / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderProgram->use();

    // Set up projection and view matrices
    glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    shaderProgram->setMat4("projection", projection);

    glm::mat4 view = camera->GetViewMatrix();
    shaderProgram->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shaderProgram->setMat4("model", model);

    // Draw the scene
    if (scene) {
        scene->draw(*shaderProgram, model);
    }

    // glfw: swap buffers and poll IO events
    glfwSwapBuffers(Pearl::window);
    glfwPollEvents();
}

bool Pearl::shouldClose() {
    return glfwWindowShouldClose(window);
}