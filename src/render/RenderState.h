#pragma once
namespace Chronos {
    class RenderState{
        public:
        virtual void setDirty(bool dirty) = 0;
        virtual bool isDirty() = 0;
        virtual void update() = 0;
        virtual void apply() = 0;
        virtual ~RenderState(){}
    };
}