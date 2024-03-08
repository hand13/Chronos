#pragma once
#include "ControlUI.h"
#include "component/Component.h"
#include "game_object/GameObject.h"
#include <render/Texture2D.h>
#include <Scene.h>

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
        public:
        ChronosEditor();
        void setScene(Scene* scene);
        void displayEditorView();
        virtual void displayOffscreen(Texture2D * rt);
        virtual ~ChronosEditor(){}
    };
}