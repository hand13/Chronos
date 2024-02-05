#pragma once
typedef size_t TypeSize;

namespace Chronos {
    enum ShaderType {
        VERTEX_SHADER
    };
}
namespace Geometry {
    enum Type {
        INT,
        FLOAT,
        DOUBLE,
        BOOL,
        VEC2,
        VEC,
        VEC4
    };
    struct Vec2 {
        float x;
        float y;
    };

    struct Vec {
        float x;
        float y;
        float z;
    };

    struct Vec4 {
        float x;
        float y;
        float z;
        float w;
    };

    inline constexpr TypeSize getSize(Type type) {
        switch(type) {
            case INT:
            return sizeof(int);
            case FLOAT:
            return sizeof(float);
            case DOUBLE:
            return sizeof(double);
            case BOOL:
            return sizeof(char);
            case VEC2:
            return sizeof(Vec2);
            case VEC:
            return sizeof(Vec);
            case VEC4:
            return sizeof(Vec4);
            default:
            return -1;
        }
    }
}
