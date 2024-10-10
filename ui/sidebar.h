// sidebar.h
#ifndef SIDEBAR_H
#define SIDEBAR_H
#ifdef _WIN32
#pragma once
#endif

#include <imgui.h>
#include "options.h"

class SideBar {
public:
    void Draw(bool& showOptions,
        ImVec4& selectedColor,
        Options option);
};

#endif