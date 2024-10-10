// main.cpp
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

float version = 0.12f;

bool showAbout = false;

// options sh$t
bool showOptions = false;
ImVec4 selectedColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

std::vector<std::unique_ptr<GameObject>> gameObjects;
std::vector<std::string> consoleLog;

void DrawUI()
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
        ImGui::Text("Alter Engine\nVersion %f", version);
        if (ImGui::Button("Close")) {
            showAbout = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    // sidebar
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

    // options
    if (showOptions) {
        ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 300) * 0.5f, (ImGui::GetIO().DisplaySize.y - 200) * 0.5f), ImGuiCond_Once);
        ImGui::OpenPopup("Options");
    }
    if (ImGui::BeginPopup("Options")) {
        ImGui::Text("Options");
        ImGui::ColorPicker3("Background Color", (float*)&selectedColor);
        if (ImGui::Button("Close")) {
            showOptions = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void UpdateAndRenderObjects(float deltaTime) {
    for (auto& object : gameObjects) {
        object->Update(deltaTime);
        object->Render();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBox(NULL, "SDL could not initialize", "Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("Alter",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        MessageBox(NULL, "Window could not be created", "Error", MB_OK | MB_ICONERROR);
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        MessageBox(NULL, "OpenGL context could not be created", "Error", MB_OK | MB_ICONERROR);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    gameObjects.push_back(std::make_unique<GameObject>("Test 1"));
    gameObjects.push_back(std::make_unique<GameObject>("Test 2"));

    bool running = true;
    SDL_Event event;
    float deltaTime = 0.0f;
    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        Uint32 currentTime = SDL_GetTicks();
        deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        DrawUI();
        UpdateAndRenderObjects(deltaTime);

        glClearColor(selectedColor.x, selectedColor.y, selectedColor.z, selectedColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
