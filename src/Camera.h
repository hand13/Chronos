#pragma once
namespace Chronos{
    class Camera {
        private:
        unsigned int  width;
        unsigned int height;
        public:
        Camera(){
            width = 0;
            height = 0;
        }
        void setWidth(unsigned int width) {
            this->width = width;
        }
        void setHeight(unsigned int height) {
            this->height = height;
        }
        unsigned int getWidth() const{
            return width;
        }
        unsigned int getHeight() const{
            return height;
        }
    };
}