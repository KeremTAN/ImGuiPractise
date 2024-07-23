#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

static char* versionOfGlsl;

enum class PanelColorType {
    Dark, Light, Classic
};

class Init {
public:

    Init() = delete;
    ~Init() {
        glfwTerminate();
    };

    inline static void run(const std::string& panelName, void(*task)(), const PanelColorType&& panelColor = PanelColorType::Dark) {
        GLFWwindow* window = init_the_panel(panelName, panelColor);
       

        while(!glfwWindowShouldClose(window)) {

            glfwPollEvents();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            task();
            
            ImGui::Render();
            int width{}, height{};
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0.f, 0.f, width, height);
            glClearColor(0.5f, 0.55f, 0.85f, 0.1f);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
        }

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(window);
    }

private:

inline static bool set_version() {

    if (!glfwInit()){
        return 1;
    }

    // Decide GL+GLSL versions
    #if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        versionOfGlsl = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    #elif defined(__APPLE__)
        // GL 3.2 + GLSL 150
        versionOfGlsl = "#version 150";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
    #else
        // GL 3.0 + GLSL 130
        *versionOfGlsl = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
    #endif

    return 0;
}

inline static GLFWwindow* create_window(const std::string& panelName) {
   
    if(set_version()) {
        std::cout << "ImGui cannot been initilazeted !" << std::endl;
        return nullptr;
    }

    GLFWwindow* window { glfwCreateWindow(1920, 1080, panelName.c_str(), nullptr, nullptr) };

    if(window == nullptr) {
        std::cout << "Window cannot been created !" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    return window;
}

inline static GLFWwindow* init_the_panel(const std::string& panelName, const PanelColorType& panelColor) {
   
    GLFWwindow* window { create_window(panelName) };
    if (window == nullptr) {
        return nullptr;
    }

    ImGui::CreateContext();
    ImGuiIO& io { ImGui::GetIO() };
    (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;

    if(panelColor == PanelColorType::Classic)
        ImGui::StyleColorsClassic();
    else if(panelColor == PanelColorType::Light)
        ImGui::StyleColorsLight();
    else ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(versionOfGlsl);

    return window;

}

}; // Init