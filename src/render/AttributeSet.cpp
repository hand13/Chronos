#include "AttributeSet.h"
#include <vcruntime.h>
namespace Geometry {

    void AttributeSet::addAttribute(const std::string& name,Type type) {
        
        int prevIndex = attributes.size()> 0? static_cast<int>(attributes.size() -1) : -1;//顶端节点

        Attribute attribute(name,type);
        attributeSet[name] = attribute;
        attributes.push_back(attribute);

        if(prevIndex < 0) {
            attributeOffsets[name] = 0;
        }else {
            Attribute& last = attributes[prevIndex];
            attributeOffsets[name] = getSize(last.dataType) + getAttributeOffset(last.name);
        }
    }

    TypeSize AttributeSet::totalSize()const {
        size_t size = attributes.size();
        if(size == 0){
            return 0;
        }
        const Attribute & attr = attributes[size-1];
        return attributeOffsets.at(attr.name) + getSize(attr.dataType);
    }

}
