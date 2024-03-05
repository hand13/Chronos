#include "TestUI.h"
#include <imgui.h>
#include <platform/windows/render/d3d11/ChronosD3D11Texture2D.h>
namespace Chronos{
    TestUI::TestUI():ControlUI(){
        srv = nullptr;
    }
    void TestUI::showWindow(){
        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
        static float s[4];
        if(ImGui::ColorPicker4("test", s) ) {
        }
        ImGui::Image(srv, ImVec2(800.f,800.f));
        ImGui::End();
    }
    void TestUI::displayOffscreen(Texture2D * rt){
        ChronosD3D11Texture2D * ct = dynamic_cast<ChronosD3D11Texture2D*>(rt);
        if(ct != nullptr){
            srv = ct->getSRV();
        }
    }
}