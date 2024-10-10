// console.cpp

#if 0 // unused
#include "console.h"

Console::Console() : scrollToBottom(true) {
    ImGuiStreamBuf* streamBuf = new ImGuiStreamBuf(*this);
    std::cout.rdbuf(streamBuf);
}

void Console::AddLog(const char* log) {
    items.push_back(log);
    if (scrollToBottom) {
        ImGui::SetScrollHereY(1.0f);
    }
}

void Console::Draw(const char* title, bool* p_open) {
    ImGui::Begin(title, p_open);

    if (ImGui::Button("Clear")) {
        Clear();
    }
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &scrollToBottom);

    ImGui::Separator();

    static char logBuffer[1024 * 16];
    logBuffer[0] = '\0';

    for (const auto& item : items) {
        strcat_s(logBuffer, (item + "\n").c_str());
    }

    ImGui::InputTextMultiline("##Logs", logBuffer, sizeof(logBuffer), ImVec2(-1, 200), ImGuiInputTextFlags_ReadOnly);

    if (ImGui::InputText("Command", &inputBuffer[0], ImGuiInputTextFlags_EnterReturnsTrue)) {
        ProcessInput();
    }

    ImGui::End();
}

void Console::Clear() {
    items.clear();
}

void Console::ProcessInput() {
    if (!inputBuffer.empty()) {
        AddLog(inputBuffer.c_str());
        ExecuteCommand(inputBuffer);
        inputBuffer.clear();
    }
}

void Console::ExecuteCommand(const std::string& command) {
    if (command == "clear") {
        Clear();
    }
    else {
        AddLog(("Unknown command: " + command).c_str());
    }
}
#endif