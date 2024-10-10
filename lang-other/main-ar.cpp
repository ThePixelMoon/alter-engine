#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <windows.h>

float version = 0.12f;

bool showAbout = false;

bool showOptions = false;
ImVec4 selectedColor = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);

void DrawUI()
{
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("ملف")) {
        ImGui::MenuItem("جديد");
        ImGui::MenuItem("فتح");
        ImGui::MenuItem("حفظ");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("تعديل")) {
        ImGui::MenuItem("تراجع");
        ImGui::MenuItem("إعادة");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("مساعدة")) {
        if (ImGui::MenuItem("حول")) {
            showAbout = true;
        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();

    if (showAbout) {
        ImGui::OpenPopup("حول");
    }
    if (ImGui::BeginPopup("حول")) {
        ImGui::Text("محرك التعديل\nالإصدار %f", version);
        if (ImGui::Button("إغلاق")) {
            showAbout = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y - ImGui::GetFrameHeight()));

    ImGui::Begin("شريط الجانب", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Spacing();
    float button_width = ImGui::CalcTextSize("خيارات").x + ImGui::GetStyle().FramePadding.x * 2;
    ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - button_width - ImGui::GetStyle().FramePadding.x);
    ImGui::SetCursorPosY(ImGui::GetContentRegionMax().y - ImGui::GetStyle().FramePadding.y - ImGui::GetFrameHeightWithSpacing());

    if (ImGui::Button("خيارات")) {
        showOptions = true;
    }

    ImGui::End();

    if (showOptions) {
        ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 300) * 0.5f, (ImGui::GetIO().DisplaySize.y - 200) * 0.5f), ImGuiCond_Once);
        ImGui::OpenPopup("خيارات");
    }
    if (ImGui::BeginPopup("خيارات")) {
        ImGui::Text("خيارات");
        ImGui::ColorPicker3("لون الخلفية", (float*)&selectedColor);
        if (ImGui::Button("إغلاق")) {
            showOptions = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBox(NULL, "لم يتمكن SDL من التهيئة", "خطأ", MB_OK | MB_ICONERROR);
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("التعديل",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        MessageBox(NULL, "لم يتمكن من إنشاء النافذة", "خطأ", MB_OK | MB_ICONERROR);
        SDL_Quit();
        return -1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        MessageBox(NULL, "لم يتمكن من إنشاء سياق OpenGL", "خطأ", MB_OK | MB_ICONERROR);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ImGui::CreateContext();
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        DrawUI();

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
