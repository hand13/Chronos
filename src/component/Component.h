#pragma once
#include <string>
#include <vector>
namespace Chronos{
    class Component {
        public:
        virtual void init() = 0;
        virtual void setParent(Component* parent) = 0;
        virtual Component* getParent() = 0;
        virtual void solve() = 0;
        virtual void setName(const std::string& name) = 0;
        virtual const std::string& getName()const = 0;
        virtual std::vector<Component*>& getChildren() = 0;
        virtual void addComponent(Component* component) = 0;
        virtual void destroy() = 0;
        virtual ~Component(){}
    };
}