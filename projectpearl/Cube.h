#pragma once

#include "Object3D.h"
#include <array>

class Cube : public Object3D {
public:
    std::array<float, 180> vertices;
    Cube(const char* texture_path, int type) {
        if (type == 0) {
            float temp_vertices[] = {
                // positions          // texture coords
                // Face 1: Front
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
                 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom-right
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
                 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left

                // Face 2: Back
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top-left
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left

                // Face 3: Left
                -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
                -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-right

                // Face 4: Right
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-left
                 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-right
                 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-right
                 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-right
                 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-left
                 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top-left

                 // Face 5: Bottom
                 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Top-left
                  0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // Top-right
                  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
                 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Top-left

                 // Face 6: Top
                 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top-left
                  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top-right
                  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom-right
                 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Bottom-left
                 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // Top-left
            };
            std::copy(std::begin(temp_vertices), std::end(temp_vertices), vertices.begin());
        }
        else if(type == 1) {
            float temp_vertices[] = {
                // Front face
                -0.5f, -0.5f, -0.5f,  1.0f / 3.0f, 0.0f,  // Bottom-left
                 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // Bottom-right
                 0.5f,  0.5f, -0.5f,  0.0f, 1.0f / 3.0f,  // Top-right
                 0.5f,  0.5f, -0.5f,  0.0f, 1.0f / 3.0f,  // Top-right
                -0.5f,  0.5f, -0.5f,  1.0f / 3.0f, 1.0f / 3.0f,  // Top-left
                -0.5f, -0.5f, -0.5f,  1.0f / 3.0f, 0.0f,  // Bottom-left

                // Back face
                -0.5f, -0.5f,  0.5f,  0.0f, 2.0f / 3.0f,  // Bottom-left
                 0.5f, -0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Bottom-right
                 0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 1.0f,  // Top-right
                 0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 1.0f,  // Top-right
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // Top-left
                -0.5f, -0.5f,  0.5f,  0.0f, 2.0f / 3.0f,  // Bottom-left

                // Left face
                -0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Top-left
                -0.5f,  0.5f, -0.5f,  2.0f / 3.0f, 2.0f / 3.0f,  // Top-right
                -0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 1.0f / 3.0f,  // Bottom-right
                -0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 1.0f / 3.0f,  // Bottom-right
                -0.5f, -0.5f,  0.5f,  1.0f / 3.0f, 1.0f / 3.0f,  // Bottom-left
                -0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Top-left

                // Right face (needs to be flipped. See the TNT block)
                 0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Top-left
                 0.5f,  0.5f, -0.5f,  2.0f / 3.0f, 2.0f / 3.0f,  // Top-right
                 0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 1.0f / 3.0f,  // Bottom-right
                 0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 1.0f / 3.0f,  // Bottom-right
                 0.5f, -0.5f,  0.5f,  1.0f / 3.0f, 1.0f / 3.0f,  // Bottom-left
                 0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Top-left

                 // Bottom face
                 -0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 2.0f / 3.0f,  // Top-left
                  0.5f, -0.5f, -0.5f,  1.0f, 2.0f / 3.0f,  // Top-right
                  0.5f, -0.5f,  0.5f,  1.0f, 1.0f / 3.0f,  // Bottom-right
                  0.5f, -0.5f,  0.5f,  1.0f, 1.0f / 3.0f,  // Bottom-right
                 -0.5f, -0.5f,  0.5f,  2.0f / 3.0f, 1.0f / 3.0f,  // Bottom-left
                 -0.5f, -0.5f, -0.5f,  2.0f / 3.0f, 2.0f / 3.0f,  // Top-left

                 // Top face
                -0.5f,  0.5f, -0.5f,  1.0f / 3.0f, 1.0f / 3.0f,  // Top-left
                 0.5f,  0.5f, -0.5f,  0.0f, 1.0f / 3.0f,        // Top-right
                 0.5f,  0.5f,  0.5f,  0.0f, 2.0f / 3.0f,        // Bottom-right
                 0.5f,  0.5f,  0.5f,  0.0f, 2.0f / 3.0f,        // Bottom-right
                -0.5f,  0.5f,  0.5f,  1.0f / 3.0f, 2.0f / 3.0f,  // Bottom-left
                -0.5f,  0.5f, -0.5f,  1.0f / 3.0f, 1.0f / 3.0f   // Top-left
            };
            std::copy(std::begin(temp_vertices), std::end(temp_vertices), vertices.begin());
        }
        
        init(vertices.data(), sizeof(vertices), texture_path);
    };

    const std::array<float, 180>& getVertices() const {
        return vertices;
    }
};
