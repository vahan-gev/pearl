#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_s.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IDGenerator.h"
class Object3D {
public:
    IDGenerator idGen;
    unsigned int VAO, VBO, texture, id;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    bool visible;

    Object3D() : position(0.0f, 0.0f, 0.0f), rotation(0.0f, 0.0f, 0.0f), scale(1.0f, 1.0f, 1.0f) {
        VAO = 0;
        VBO = 0;
        texture = 0;
        id = idGen.generateID(100000);
        visible = true;
    }

    void init(const float* vertices, size_t vertexSize, const char* texture_path) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Load and create a texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // GL_NEAREST for pixelated look and GL_LINEAR for smooth look
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
        if (data) {
            GLenum format = GL_RGB;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            else if (nrChannels == 4)
                format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
    }

    void draw(Shader& shaderProgram, glm::mat4 modelView) const {
        shaderProgram.use();
        glm::mat4 model = glm::translate(modelView, position);
        model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
        model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
        model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));
        model = glm::scale(model, scale);
        shaderProgram.setMat4("model", model);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteTextures(1, &texture);
    }
};
