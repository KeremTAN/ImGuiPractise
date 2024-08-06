#pragma once
#include "../includes/Init.h"



inline void task_5() {

   //ImGui::ColorEdit3("set color", (float*)&colors); 
   static std::string pathText{};

   ImGui::Begin("File Selector");

   if(ImGui::Button("Choose..")) {
      ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Select", ".txt, .cpp");
   }

   if(ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if(ImGuiFileDialog::Instance()->IsOk()) {
            std::string path { ImGuiFileDialog::Instance()->GetFilePathName() };
            size_t ix { path.find_last_of('/') };
            pathText = path.substr(ix+1);
        }
        ImGuiFileDialog::Instance()->Close();
   }

   ImGui::Text("Selected File's name is %s", pathText.c_str());
   ImGui::End();
}

inline void task_4() {
    ImGui::Begin("Hotel");
    if(ImGui::TreeNode("Hotel Olala")) {
        ImGui::TextWrapped("Text Wrapped Ne?");
        ImGui::Separator(); // for line

        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
        if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags)) {
            if (ImGui::BeginTabItem("Information")) {
                if(ImGui::BeginMenu("Foods")) {
                    if(ImGui::MenuItem("Meals")) {}
                    if(ImGui::MenuItem("Vegetables")) {}
                    if(ImGui::MenuItem("Pastas")) {}
                    if(ImGui::BeginMenu("Drinks")) {
                        if(ImGui::BeginMenu("Alcohols")) {
                            ImGui::MenuItem("Coctail");
                            ImGui::EndMenu();
                        }
                        if(ImGui::BeginMenu("Softs")) {
                            ImGui::MenuItem("Soda");
                            ImGui::EndMenu();
                        }
                        ImGui::EndMenu();
                    } // Drinks
                    ImGui::EndMenu();
                } // Foods
                if(ImGui::BeginMenu("Travel Points")) {
                    ImGui::MenuItem("Show Travel Points On Map", "CTRL+M");
                    ImGui::EndMenu();
                } // Travel Points
                ImGui::EndTabItem();
            } // Information 
            if (ImGui::BeginTabItem("Rezervation")) {
                ImGui::Text("There are no rooms left in the hotel");
                ImGui::EndTabItem();
            } // Rezervation
            ImGui::EndTabBar();
        } // MyTabBar

        ImGui::TreePop();
    } // Information
    ImGui::End();
}

inline void task_3() {
    static std::vector<float> xs(100), ys(100);
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        std::array<float, 100> ss;

    for (int i = 0; i < 100; ++i) {
        xs[i] = i * 0.1f;
        ys[i] = std::sin(xs[i]);
        ss[i] = std::sin(xs[i]);

    }

    ImGui::PlotHistogram("Plot Histogram", ss.begin(), 100, 0, NULL, 0.0f, 1.0f,  ImVec2(0, 80.0f));
}

inline void task_2() {
    static char ch[20];
    ImGui::Begin("Window 1");
    ImGui::Text("Isim");
    ImGui::SameLine();
    ImGui::InputText("##", ch, IM_ARRAYSIZE(ch));
    ImGui::End();

    static int8_t yas{};
    ImGui::Begin("Window 2");
    ImGui::SliderInt("Enter your age", (int*)&yas, 12, 101);
    ImGui::SameLine();
    ImGui::End();

}

inline void task_1() {
    static char mt[512];
    {
        ImGui::Begin("Multi Text");
        ImGui::Text("Burada Tree");
        if(ImGui::TreeNode("MultiLine")){
            ImGui::InputTextMultiline("##Text", mt, IM_ARRAYSIZE(mt), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 10), 0);
            ImGui::Text("%s", mt);
            ImGui::TreePop();
        }
        ImGui::End();
    }
}

inline void task_0() {
    static bool isTrue = false;
     
    ImGui::Begin("Say My Name");

    ImGui::Text("The New TEXT !");
    ImGui::Checkbox("isTrue", &isTrue);
            
            
    if(ImGui::Button("Close me")) 
        return;

    ImGui::End();

}