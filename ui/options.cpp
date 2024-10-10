// options.cpp
#include "options.h"

void Options::Draw(bool& showOptions,
                   ImVec4& selColor)
{
    if (showOptions) {
        ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 300) * 0.5f, (ImGui::GetIO().DisplaySize.y - 200) * 0.5f), ImGuiCond_Once);
        ImGui::OpenPopup("Options");
    }

    if (ImGui::BeginPopup("Options")) {
        ImGui::Text("Options");

        ImGui::ColorPicker3("Background Color", (float*)&selColor);

        if (ImGui::Button("Close")) {
            showOptions = false;
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}