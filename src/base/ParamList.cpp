#include "ParamList.h"

#include <cstddef>

#include "Param.h"
#include "Utils.h"

namespace Chronos {

void ParamList::destroyParams() {
    for (int i = 0; i < params.size(); i++) {
        if (params[i]) {
            delete params[i];
        }
        params[i] = 0;
    }
}

ParamList::ParamList() {}

void ParamList::registerParam(const std::string& name, ParamType type,
                              PackInfo packInfo, size_t rawDataSize) {
    Param* res = constructParamFromType(name, type, packInfo, rawDataSize);
    params.push_back(res);
    paramIndex[name] = static_cast<unsigned int>(params.size() - 1);
    if (res->signature().type == SPTEXTURE2D) {
        return;  // pack ignore texture
    }
    appendPackInfo(name, res->signature().size, packInfo);
}

bool ParamList::checkParam(const std::string& paramName,
                           const ParamSignature& ps) const {
    return paramIndex.find(paramName) != paramIndex.end() &&
           params[paramIndex.at(paramName)]->signature() == ps;
}

Param* ParamList::getParam(const std::string& name) {
    if (paramIndex.find(name) == paramIndex.end()) {
        return nullptr;
    }
    return params[paramIndex.at(name)];
}

const std::vector<Param*>& ParamList::getParamList() const { return params; }
ParamList::~ParamList() { destroyParams(); }

RawData ParamList::packDataInSlot(u8 slot) {
    u16 sz = slotAndSize[slot];
    if ((sz % MAX_PACK_SIZE) != 0) {  // 对其 float4
        sz += MAX_PACK_SIZE - (sz % MAX_PACK_SIZE);
    }
    RawData rd(sz);
    for (auto p : params) {
        if (Slot(p->getPackInfo()) != slot ||
            p->signature().type == SPTEXTURE2D) {
            continue;
        }
        void* data = p->asData();
        size_t size = p->signature().size;
        u16 offset = offset_data[p->getName()];
        rd.copyIntoThis(static_cast<u8*>(data), 0, offset, size);
    }
    return rd;
}

const std::map<u8, u16>& ParamList::getAllSlotAndSize() const {
    return slotAndSize;
}

void ParamList::appendPackInfo(const std::string& paramName, size_t size,
                               PackInfo packInfo) {
    u8 slot = Slot(packInfo);
    // u16 packOffset = POffset(packInfo);//todo
    u16 currentSlotSize = slotAndSize[slot];
    u16 t_size = static_cast<u16>(size);
    u16 t_offset = currentSlotSize;
    u16 pack_size = static_cast<u16>(size);

    if (pack_size >= MAX_PACK_SIZE ||
        ((currentSlotSize % MAX_PACK_SIZE + pack_size) >
         MAX_PACK_SIZE)) {  // float4塞不下
        if (currentSlotSize % MAX_PACK_SIZE != 0) {
            u16 bias = MAX_PACK_SIZE - (currentSlotSize % MAX_PACK_SIZE);
            t_size += bias;
            t_offset += bias;
        }
    }

    slotAndSize[slot] = currentSlotSize + t_size;
    offset_data[paramName] = t_offset;
}

u8 ParamList::getTexturesCount() {
    u8 count = 0;
    for (auto p : params) {
        if (p->signature().type == SPTEXTURE2D) {
            count++;
        }
    }
    return count;
}
}  // namespace Chronos