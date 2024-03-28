#include "reflect_bp.h"

#include <cstddef>

#include "head_for_reflect.h"
#include "reflect_api/Klass.h"


void load_reflect_test(Metaspace* ms) {
    Klass* ks = new Klass("ReflectTest", false, sizeof(ReflectTest));
    Field idField;
    idField.access = Public;
    idField.name = "id";
    idField.metaInfo.marked = true;
    idField.valueType.rawName = "int";
    idField.valueType.trueName = "int";
    idField.valueType.type = Value;
    idField.valueType.klass = nullptr;
    idField.offset = offsetof(ReflectTest, id);
    ks->fields.push_back(idField);
    ms->reg(ks);
}