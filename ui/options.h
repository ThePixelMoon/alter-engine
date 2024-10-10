// options.h
#ifndef OPTIONS_H
#define OPTIONS_H
#ifdef _WIN32
#pragma once
#endif

#include <imgui.h>
extern bool darkTheme;

class Options {
public:
	void Draw(bool& showOptions);
};

#endif