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
#include "EventBridge.h"

namespace Chronos{
    class ChronosEditor :public ControlUI{
        private:
        EventBridge eventBridge;
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
        virtual void processMsg(const MSG & msg)override;


        void showbool(bool& b,boolean editable,const char * label);

        void showi8(i8& i,boolean eidtable,const char * label);
        void showi16(i16& i,boolean eidtable,const char * label);
        void showi32(i32& i,boolean editable,const char * label);
        void showi64(i64& i,boolean editable,const char * label);

        void showu8(u8& i,boolean eidtable,const char * label);
        void showu16(u16& i,boolean eidtable,const char * label);
        void showu32(u32& i,boolean editable,const char * label);
        void showu64(u64& i,boolean editable,const char * label);

        void showf32(f32& f,boolean editable,const char * label);
        void showf64(f64& f,boolean editable,const char * labal);

        void showFloat2(Float2& f2,boolean editable,const char * label);
        void showFloat3(Float3& f3,boolean editable,const char * label);
        void showFloat4(Float4& f4,boolean editable,const char * label);

        void showPrimaryObject(void * object,const Klass* klass,const char * name);
        bool showSpecialObject(void *object,const Klass* klass,const char * name);
        void showObject(void * object,const Klass* klass,const char * name);
    };
}