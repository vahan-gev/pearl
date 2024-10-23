#pragma once
#include "stb_image.h"
#include <iostream> 
#include <variant> 
#include <vector>
#include "shader_s.h"
#include "Object2D.h"
#include "Object3D.h"
#include <optional>
class Scene {
public:
    std::vector<std::variant<Object2D*, Object3D*>> items;

    template<typename T>
    void add(T* item) {
        if constexpr (std::is_base_of_v<Object2D, T>) {
            items.emplace_back(static_cast<Object2D*>(item));
        }
        else if constexpr (std::is_base_of_v<Object3D, T>) {
            items.emplace_back(static_cast<Object3D*>(item));
        }
        else {
            static_assert(always_false<T>::value, "[Scene.h] > Only objects derived from Object2D or Object3D can be added to the scene");
        }
    }

    void remove(unsigned int id) {
        items.erase(std::remove_if(items.begin(), items.end(), [id](const auto& element) {
            return std::visit([id](auto* itemInList) {
                return itemInList->id == id;
                }, element);
            }), items.end());
    }

    std::optional<std::variant<Object2D*, Object3D*>> getItemByID(unsigned int id) {
        for (const auto& element : items) {
            std::variant<Object2D*, Object3D*> item = element;
            if (std::visit([id](auto* obj) {
                return obj->id == id;
                }, item)) {
                return item;
            }
        }
        return std::nullopt;
    }

    void draw(Shader& shaderProgram, glm::mat4 model) {
        for (const auto& element : items) {
            std::visit([&shaderProgram, &model](const auto& item) {
                if (item->visible) {
                    item->draw(shaderProgram, model);
                }
                }, element);
        }
    }

    ~Scene() {
		for (const auto& element : items) {
			std::visit([](auto& item) {
                item->cleanup();
				delete item;
				}, element);
		}
	}

private:
    template<class T>
    struct always_false : std::false_type {};
};