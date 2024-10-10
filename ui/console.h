// console.h
#ifndef CONSOLE_H
#define CONSOLE_H
#ifdef _WIN32
#pragma once
#endif

#if 0 // unused
#include <vector>
#include <string>
#include <imgui.h>
#include <iostream>

class Console {
public:
    Console();
    void AddLog(const char* log);
    void Draw(const char* title = "Console", bool* p_open = nullptr);
    void Clear();
    void ExecuteCommand(const std::string& command);

private:
    std::vector<std::string> items;
    std::string inputBuffer;
    bool scrollToBottom;

    void ProcessInput();
};

class ImGuiStreamBuf : public std::streambuf {
public:
    ImGuiStreamBuf(Console& console) : console(console) {}

protected:
    virtual int overflow(int c) override {
        if (c != EOF) {
            console.AddLog(std::string(1, static_cast<char>(c)).c_str());
        }
        return c;
    }

    virtual int sync() override {
        return 0;
    }

private:
    Console& console;
};
#endif

#endif