#include "TestUI.h"
#include "imgui.h"
namespace Chronos{
    void TestUI::showWindow(){
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        static float s[4];
        if(ImGui::ColorPicker4("test", s) ) {
        }
        ImGui::End();
    }
}