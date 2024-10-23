#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader_s.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IDGenerator.h"
class Object2D {
public:
	unsigned int VAO, VBO, EBO, texture, id;
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    IDGenerator idGen;
    bool visible;
	Object2D() {
		this->VAO = 0;
		this->VBO = 0;
		this->EBO = 0;
		this->texture = 0;
        this->id = idGen.generateID(100000);
        this->visible = true;
	}

    void init(const float* vertices, const unsigned int* indices, size_t vertexSize, size_t indexSize, const char* texture_path) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // Texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Load and create a texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        unsigned char* data = stbi_load(texture_path, &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);
        stbi_set_flip_vertically_on_load(true);
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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

    void cleanup() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteTextures(1, &texture);
    }
};