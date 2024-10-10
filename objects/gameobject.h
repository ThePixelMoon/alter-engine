// gameobject.h
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#ifdef _WIN32
#pragma once
#endif

#include <string>
#include <vector>
#include <memory>

class GameObject {
public:
    GameObject(const std::string& name) : name(name), position{ 0.0f, 0.0f, 0.0f }, rotation{ 0.0f, 0.0f, 0.0f }, scale{ 1.0f, 1.0f, 1.0f } {}

    void Update(float deltaTime);
    void Render();

    void SetPosition(float x, float y, float z) { position[0] = x; position[1] = y; position[2] = z; }
    void SetRotation(float x, float y, float z) { rotation[0] = x; rotation[1] = y; rotation[2] = z; }
    void SetScale(float x, float y, float z) { scale[0] = x; scale[1] = y; scale[2] = z; }

    const std::string& GetName() const { return name; }

private:
    std::string name;
    float position[3];
    float rotation[3];
    float scale[3];
};

#endif