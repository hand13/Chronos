#pragma once
#include "ControlUI.h"
#include "base/Event.h"
#include "base/Utils.h"
#include <component/Component.h>
#include "game_object/GameObject.h"
#include <reflect_api/Field.h>
#include <reflect_api/Klass.h>
#include <render/Texture2D.h>
#include <engine/Scene.h>
#include <vector>
#include <reflect_api/Metaspace.h>

namespace Chronos{
    class ChronosEditor :public ControlUI{
        protected:
        Metaspace metaspace;//todo,only for editor
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

        protected:


        void showbool(bool& b,boolean editable);

        void showi8(i8& i,boolean eidtable);
        void showi16(i16& i,boolean eidtable);
        void showi32(i32& i,boolean editable);
        void showi64(i64& i,boolean editable);

        void showu8(u8& i,boolean eidtable);
        void showu16(u16& i,boolean eidtable);
        void showu32(u32& i,boolean editable);
        void showu64(u64& i,boolean editable);

        void showf32(f32& f,boolean editable);
        void showf64(f64& f,boolean editable);

        void showFloat2(Float2& f2,boolean editable,const char * name);
        void showFloat3(Float3& f3,boolean editable,const char * name);

        void showPrimaryObject(void * object,const Klass* klass,const char * name);
        bool showSpecialObject(void *object,const Klass* klass,const char * name);
        void showObject(void * object,const Klass* klass,const char * name);
    };
}