// options.h
#ifndef OPTIONS_H
#define OPTIONS_H
#ifdef _WIN32
#pragma once
#endif

#include <imgui.h>

class Options {
public:
	void Draw(bool& showOptions,
			  ImVec4& selColor);
};

#endif