// gameobject.cpp
#include "gameobject.h"
#include <iostream>

void GameObject::Update(float deltaTime) {
#ifdef _DEBUG
    std::cout << "Updating GameObject: " << name << " at position ("
        << position[0] << ", " << position[1] << ", " << position[2] << ")\n";
#endif
}

void GameObject::Render() {
#ifdef _DEBUG
    std::cout << "Rendering GameObject: " << name << " with scale ("
        << scale[0] << ", " << scale[1] << ", " << scale[2] << ")\n";
#endif
}