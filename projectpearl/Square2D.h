#pragma once
#include "Object2D.h"

class Square2D : public Object2D {
public:
    char* texture_path;
    // Set up vertex data
    
    float vertices[32] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[6] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Square2D(const char* texture_path) {
        this->texture_path = new char[strlen(texture_path) + 1];
        strcpy_s(this->texture_path, strlen(texture_path) + 1, texture_path);
        init(vertices, indices, sizeof(vertices), sizeof(indices), this->texture_path);
    }
};
