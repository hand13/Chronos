#include "ChronosEditor.h"
#include "engine/ChronosEngine.h"
#include "engine/Scene.h"
#include "base/Transform.h"
#include "base/Utils.h"
#include "component/Component.h"
#include "component/TransformComponent.h"
#include "game_object/GameObject.h"
#include <imgui.h>
namespace Chronos{

    ChronosEditor::ChronosEditor():ControlUI(){
        srv = nullptr;
        currentScene = nullptr;
        selectedObject = nullptr;
        selectedComponent = nullptr;
    }

    void ChronosEditor::setScene(Scene*s){
        currentScene = s;
    }

    void ChronosEditor::showWindow(){

        static bool use_work_area = true;
        static bool open = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings| ImGuiWindowFlags_MenuBar;

        // We demonstrate using the full viewport area or the work area (without menu-bars, task-bars etc.)
        // Based on your use case you may want one of the other.
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        if (ImGui::Begin("Example: Fullscreen window",&open, flags)) {
            displayEditorView();
        }
        ImGui::End();
    }
    void ChronosEditor::displayEditorView(){
        showMenuBar();
        showEditorArea();
    }

    void ChronosEditor::showEditorArea(){
        SizeU size =  Engine->getSize();
        // Right
        {
            ImGui::BeginGroup();
            ImGui::BeginChild("Main View", ImVec2(static_cast<float>(size.width), 0)); // Leave room for 1 line below us
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
                if (ImGui::BeginTabItem("Render View")) {
                    showRenderView();
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Details")) {
                    // ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            // if (ImGui::Button("Revert")) {}
            // ImGui::SameLine();
            // if (ImGui::Button("Save")) {}
            ImGui::EndGroup();

        }
        ImGui::SameLine();
        {
            ImGui::BeginChild("left pane", ImVec2(0, 0), true);

            ImGui::BeginChild("objects",ImVec2(0,400.f));
            showObjectListView();
            ImGui::EndChild();

            ImGui::Separator();

            ImGui::BeginChild("object_detail",ImVec2(0,0));
            showGameObjectDetailView();
            ImGui::EndChild();

            ImGui::EndChild();
        }

    }

    void ChronosEditor::showMenuBar(){
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Close")){}
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
    }
    void ChronosEditor::showObjectListView(){
        if(currentScene != nullptr){
            for(auto obj:currentScene->getAllGameObjects()){
                if(ImGui::Selectable(obj.first.c_str(),selectedObject == obj.second.get())){
                    selectedObject = obj.second.get();
                }
            }
        }
    }

    void ChronosEditor::showRenderView(){
        SizeU size =  Engine->getSize();
        ImGui::Image(srv, ImVec2(static_cast<float>(size.width),static_cast<float>(size.height)));
    }

    void ChronosEditor::showGameObjectDetailView(){
        ImGui::BeginChild("object_information",ImVec2(0,200.f));
        showComponentListView();
        ImGui::EndChild();

        ImGui::Separator();

        ImGui::BeginChild("component_detial",ImVec2(0,0));
        showComponentDetailView();
        ImGui::EndChild();
    }
    void ChronosEditor::showComponentListView(){
        if(selectedObject){
            Component * c =  selectedObject->getRootComponent();
            recursiveShowComponent(c);
        }
    }

    void ChronosEditor::recursiveShowComponent(Component * c){
        if(c != nullptr){
            if(ImGui::Selectable(c->getName().c_str(),selectedComponent == c)){
                selectedComponent = c;
            }
            ImGui::Indent();
            for(auto nc : c->getChildren()){
                recursiveShowComponent(nc);
            }
            ImGui::Unindent();
        }
    }

    void ChronosEditor::showComponentDetailView(){
        if(selectedComponent){
            TransformComponent* tc = dynamic_cast<TransformComponent*>(selectedComponent);
            if(tc){
                Transform& t = tc->transform;
                ImGui::InputFloat3("position", (float*)&t.pos);
            }
        }
    }

    void ChronosEditor::displayOffscreen(void * thandler){
        srv = (ID3D11ShaderResourceView*) thandler;
    }
}