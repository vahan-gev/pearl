#pragma once

#include <vector>
#include <unordered_map>
#include "Cube.h"
#include "Object3D.h"

/*
    THIS IS A WORK IN PROGRESS
*/


class Chunk : public Object3D {
public:
    static const int CHUNK_SIZE = 16;
    static const int CHUNK_HEIGHT = 256;

    std::vector<std::vector<std::vector<int>>> blocks;
    std::unordered_map<int, Cube*> blockTypes;

    Chunk(int chunkX, int chunkZ) : Object3D() {
        position = glm::vec3(chunkX * CHUNK_SIZE, 0, chunkZ * CHUNK_SIZE);
        blocks.resize(CHUNK_SIZE, std::vector<std::vector<int>>(CHUNK_HEIGHT, std::vector<int>(CHUNK_SIZE, 0)));
    }

    void addBlockType(int id, const char* texturePath, int textureType) {
        blockTypes[id] = new Cube(texturePath, textureType);
    }

    void setBlock(int x, int y, int z, int blockId) {
        if (x >= 0 && x < CHUNK_SIZE && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_SIZE) {
            blocks[x][y][z] = blockId;
        }
    }

    void generateMesh() {
        std::vector<float> vertices;

        for (int x = 0; x < CHUNK_SIZE; ++x) {
            for (int y = 0; y < CHUNK_HEIGHT; ++y) {
                for (int z = 0; z < CHUNK_SIZE; ++z) {
                    int blockId = blocks[x][y][z];
                    if (blockId != 0) {
                        Cube* block = blockTypes[blockId];
                        addBlockToMesh(vertices, x, y, z, block);
                    }
                }
            }
        }

        init(vertices.data(), vertices.size() * sizeof(float), "");
    }

private:
    void addBlockToMesh(std::vector<float>& vertices, int x, int y, int z, Cube* block) {
        for (int i = 0; i < 180; i += 5) {
            vertices.push_back(block->getVertices()[i] + x);
            vertices.push_back(block->getVertices()[i + 1] + y);
            vertices.push_back(block->getVertices()[i + 2] + z);
            vertices.push_back(block->getVertices()[i + 3]);
            vertices.push_back(block->getVertices()[i + 4]);
        }
    }
};