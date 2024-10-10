// scene.cpp
#include "scene.h"

void Scene::Update(float deltaTime) {
    for (const auto& gameObject : gameObjects) {
        gameObject->Update(deltaTime);
    }
}

void Scene::Render() {
    for (const auto& gameObject : gameObjects) {
        gameObject->Render();
    }
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject) {
    gameObjects.push_back(gameObject);
}
