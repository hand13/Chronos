#pragma once
#include <vcruntime.h>

#include <map>
#include <string>
#include <vector>

#include "Types.h"

namespace Geometry {

class Attribute {
   public:
    std::string name;
    Type dataType;
    Attribute() {}
    Attribute(const std::string& name, Type dataType)
        : name(name), dataType(dataType) {}
};

class AttributeSet {
   private:
    std::map<std::string, Attribute> attributeSet;
    std::vector<Attribute> attributes;
    std::map<std::string, TypeSize> attributeOffsets;

   public:
    AttributeSet() {}
    void addAttribute(const std::string& name, Type type);
    inline TypeSize getAttributeOffset(const std::string& attributeName) const {
        return attributeOffsets.at(attributeName);
    }

    inline const std::vector<Attribute>& getAttributes() const {
        return attributes;
    }

    inline const Attribute& getAttribute(
        const std::string& attributeName) const {
        return attributeSet.at(attributeName);
    }
    inline size_t getAttributesLength() const { return attributes.size(); }
    TypeSize totalSize() const;
};
};  // namespace Geometry