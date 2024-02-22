#pragma once
#include "ControlUI.h"

namespace Chronos{
    class TestUI :public ControlUI{
        protected:
        virtual void showWindow()override;
        public:
        virtual ~TestUI(){}
    };
}