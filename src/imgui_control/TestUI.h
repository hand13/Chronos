#pragma once
#include "ControlUI.h"
#include "../render/Texture2D.h"

namespace Chronos{
    class TestUI :public ControlUI{
        protected:
        virtual void showWindow()override;
        ID3D11ShaderResourceView* srv;
        public:
        TestUI();
        virtual void displayOffscreen(Texture2D * rt);
        virtual ~TestUI(){}
    };
}