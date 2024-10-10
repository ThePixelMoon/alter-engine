// sidebar.cpp
#include "sidebar.h"

void SideBar::Draw(bool& showOptions, Options& options)
{
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y - ImGui::GetFrameHeight()));

    ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Spacing();

    float button_width = ImGui::CalcTextSize("Options").x + ImGui::GetStyle().FramePadding.x * 2;
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - button_width - ImGui::GetStyle().FramePadding.x);
    ImGui::SetCursorPosY(ImGui::GetContentRegionMax().y - ImGui::GetStyle().FramePadding.y - ImGui::GetFrameHeightWithSpacing());

    if (ImGui::Button("Options")) {
        showOptions = !showOptions;
    }

    ImGui::End();

    options.Draw(showOptions);
}