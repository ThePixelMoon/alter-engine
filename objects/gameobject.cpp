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
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(position[0] - scale[0] / 2, position[1] - scale[1] / 2);
    glVertex2f(position[0] + scale[0] / 2, position[1] - scale[1] / 2);
    glVertex2f(position[0] + scale[0] / 2, position[1] + scale[1] / 2);
    glVertex2f(position[0] - scale[0] / 2, position[1] + scale[1] / 2);
    glEnd();
}