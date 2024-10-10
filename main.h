// main.h
#ifndef MAIN_H
#define MAIN_H
#ifdef _WIN32
#pragma once
#endif

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <windows.h>
#include <vector>

// objects, ui
#include "gameobject.h"
#include "scene.h"
#include "topbar.h"
#include "sidebar.h"
#include "options.h"

float version = 0.13f;

bool showAbout = false;
bool showOptions = false;

bool darkTheme = true;

std::vector<std::unique_ptr<GameObject>> gameObjects;

// registering the ui elements
TopBar topbar;
SideBar sidebar;
Options options;

#endif