// topbar.h
#ifndef TOPBAR_H
#define TOPBAR_H
#ifdef _WIN32
#pragma once
#endif

#include <imgui.h>

class TopBar {
public:
    void Draw(bool& showAbout);
};

#endif