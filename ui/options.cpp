// options.cpp
#include "options.h"

void Options::Draw(bool& showOptions)
{
    if (showOptions) {
        ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 300) * 0.5f, (ImGui::GetIO().DisplaySize.y - 200) * 0.5f), ImGuiCond_Once);
        ImGui::OpenPopup("Options");
    }

    if (ImGui::BeginPopup("Options")) {
        ImGui::Text("Options");

        if (ImGui::Button("Light Theme"))
            darkTheme = false;

        ImGui::SameLine();

        if (ImGui::Button("Dark Theme"))
            darkTheme = true;

        if (ImGui::Button("Close")) {
            showOptions = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}