#pragma once
#include "ControlUI.h"
#include "base/Event.h"
#include "component/Component.h"
#include "game_object/GameObject.h"
#include <render/Texture2D.h>
#include <engine/Scene.h>
#include <vector>

namespace Chronos{
    class ChronosEditor :public ControlUI{
        protected:
        virtual void showWindow()override;
        ID3D11ShaderResourceView* srv;
        Scene* currentScene;
        GameObject* selectedObject;
        Component * selectedComponent;
        void showMenuBar();
        void showEditorArea();
        void showRenderView();
        void showObjectListView();
        void showGameObjectDetailView();
        void showComponentDetailView();
        void showComponentListView();
        void recursiveShowComponent(Component * c);
        void displayEditorView();
        public:
        ChronosEditor();
        void setScene(Scene* scene);
        virtual void displayOffscreen(void* thandler);
        std::vector<IOEvent> getEvents();
        virtual ~ChronosEditor();
    };
}