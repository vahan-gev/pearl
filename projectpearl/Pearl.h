#ifndef PEARL_H
#define PEARL_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Camera.h"
class Pearl {
public:
    Pearl(Camera* cam);
    int initialize();
    void draw(Scene* scene);
    static GLFWwindow* window;
    bool shouldClose();
    static void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
private:
    Camera* camera;

    // Add these static members
    static Camera* s_camera;
    static bool s_firstMouse;
    static float s_lastX, s_lastY;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
#endif