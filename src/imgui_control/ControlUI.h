#pragma once
#include <Windows.h>
namespace Chronos {
    class ControlUI{
        private:
        bool finished;
        bool cleaned;
        HWND hWnd;
        protected:
        virtual void showWindow() = 0;
        virtual void cleanResource();
        public:
        ControlUI();
        void init();
        void runInLoop();
        void quit();
        virtual ~ControlUI();
    };
}