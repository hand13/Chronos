#pragma once
namespace Chronos {

    struct TextureParameter{
        unsigned int width;
        unsigned int height;
    };
    class Texture {
        public:
        virtual ~Texture(){}
    };

}