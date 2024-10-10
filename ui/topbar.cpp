// topbar.cpp
#include "topbar.h"

void TopBar::Draw(bool& showAbout)
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
        ImGui::MenuItem("New");
        ImGui::MenuItem("Open");
        ImGui::MenuItem("Save");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Edit")) {
        ImGui::MenuItem("Undo");
        ImGui::MenuItem("Redo");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Help")) {
        if (ImGui::MenuItem("About")) {
            showAbout = !showAbout;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if (showAbout) {
        ImGui::OpenPopup("About");
    }
    if (ImGui::BeginPopup("About")) {
        ImGui::Text("Alter Engine\nVersion %f", 0.12f);
        if (ImGui::Button("Close")) {
            showAbout = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}