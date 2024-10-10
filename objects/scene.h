// scene.h
#ifndef SCENE_H
#define SCENE_H
#ifdef _WIN32
#pragma once
#endif

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include "GameObject.h"

class Scene : public GameObject {
public:
    Scene(const std::string& name) : GameObject(name) {}
    virtual ~Scene() {}

    virtual void Init() = 0;
    virtual void Update(float deltaTime);
    virtual void Render();
    virtual void Cleanup() = 0;

    void AddGameObject(std::shared_ptr<GameObject> gameObject);
    const std::vector<std::shared_ptr<GameObject>>& GetGameObjects() const { return gameObjects; }

protected:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
};

#endif