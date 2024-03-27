#include "ChronosEditor.h"
#include "base/Event.h"
#include "base/Log.h"
#include "engine/ChronosEngine.h"
#include "engine/Scene.h"
#include "base/Utils.h"
#include "component/Component.h"
#include "game_object/GameObject.h"
#include "reflect_api/Field.h"
#include "reflect_api/Klass.h"
#include <imgui.h>
#include <vector>
#include <load_all.h>
namespace Chronos{

    ChronosEditor::ChronosEditor():ControlUI(){
        srv = nullptr;
        currentScene = nullptr;
        selectedObject = nullptr;
        selectedComponent = nullptr;

        load_all(&metaspace);
        metaspace.solveLink();
        logger = Logger::get("editor");
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

    void ChronosEditor::processMsg(const MSG & msg){
        eventBridge.pushMSG(msg);
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
        if(currentScene->getState() == SC_RUNNING){
            if(ImGui::Button("pause")){
                currentScene->pause();
            }
        }else if(currentScene->getState() == SC_PAUSED){
            if(ImGui::Button("resume")){
                currentScene->resume();
            }
        }
        auto startPoint = ImGui::GetCursorScreenPos();
        ImGui::Image(srv, ImVec2(static_cast<float>(size.width),static_cast<float>(size.height)));
        // // ImGui::SameLine();
        // // tmp = ImGui::GetCursorScreenPos();
        u32 startX = static_cast<u32>(startPoint.x);
        u32 startY = static_cast<u32>(startPoint.y);
        RectU rect(startX,startY,startX + size.width ,startY + size.height);
        eventBridge.setRect(rect);
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
            const std::string typeinfoname = typeid(*selectedComponent).name();
            Klass * klass = metaspace.getKlass(selectedComponent);
            if(klass){
                showObject(selectedComponent,klass,selectedComponent->getName().c_str());
            }
        }
    }

    void ChronosEditor::displayOffscreen(void * thandler){
        srv = (ID3D11ShaderResourceView*) thandler;
    }
    std::vector<IOEvent> ChronosEditor::getEvents(){
        std::vector<IOEvent> res = eventBridge.getEvents();
        eventBridge.clean();
        return res;
    }
    ChronosEditor::~ChronosEditor(){
        logger.info("editor destructed");
    }

    void ChronosEditor::showbool(bool& b,boolean editable,const char * label){
        ImGui::Checkbox(label, &b);
    }

    void ChronosEditor::showi8(i8& i,boolean eidtable,const char * label){

    }
    void ChronosEditor::showi16(i16& i,boolean eidtable,const char * label){

    }
    void ChronosEditor::showi32(i32& i,boolean editable,const char * label){
        ImGui::InputInt(label, &i);
    }
    void ChronosEditor::showi64(i64& i,boolean editable,const char * label){

    }

    void ChronosEditor::showu8(u8& i,boolean eidtable,const char * label){

    }
    void ChronosEditor::showu16(u16& i,boolean eidtable,const char * label){

    }
    void ChronosEditor::showu32(u32& i,boolean editable,const char * label){
    }

    void ChronosEditor::showu64(u64& i,boolean editable,const char * label){

    }

    void ChronosEditor::showf64(f64& f,boolean editable,const char * label){
        ImGui::InputDouble(label, &f);
    }

    void ChronosEditor::showf32(f32& f,boolean editable,const char * label){
        ImGui::InputFloat(label, &f);
    }

    void ChronosEditor::showFloat2(Float2& f2,boolean editable,const char * label){
        ImGui::InputFloat2(label, (float*)&f2);
    }
    void ChronosEditor::showFloat3(Float3& f3,boolean editable,const char * label){
        ImGui::InputFloat3(label, (float*)&f3);
    }

    void ChronosEditor::showFloat4(Float4& f4,boolean editable,const char * label){
        ImGui::InputFloat4(label, (float*)&f4);
    }

    void ChronosEditor::showPrimaryObject(void * object,const Klass * klass,const char * name){
        if(klass == metaspace.i32class() || klass == metaspace.intclass()){
            showi32(klass->getRef<int>(object), true,name);
            return;
        }
        if(klass == metaspace.f32class() || klass == metaspace.floatclass()){
            showf32(klass->getRef<float>(object), true,name);
            return;
        }
    }

    bool ChronosEditor::showSpecialObject(void * object,const Klass* klass,const char * name){
        if(klass == metaspace.getKlass<Float2>()){
            showFloat2(klass->getRef<Float2>(object),true,name);
            return true;
        }
        if(klass == metaspace.getKlass<Float3>()){
            showFloat3(klass->getRef<Float3>(object),true,name);
            return true;
        }
        return false;
    }

    void ChronosEditor::showObject(void * object,const Klass * klass,const char * name){
        if(klass->isPrimitiveType){
            showPrimaryObject(object,klass,name);
            return;
        }
        for(const Field& f: klass->fields){
            if(f.valueType.klass != nullptr){

                if(showSpecialObject(f.getPointer<void>(object),f.valueType.klass,f.name.c_str())){
                    continue;
                }

                showObject(f.getPointer<void>(object),f.valueType.klass,f.name.c_str());
            }
        }
    }
}