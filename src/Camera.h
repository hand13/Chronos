#pragma once
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
namespace Chronos{

    struct CameraBuffer{
        Eigen::Matrix4f viewMatrix;
        Eigen::Matrix4f projectionMatrix;
    };

    class Camera {

        private:
        unsigned int  width;
        unsigned int height;
        bool shouldUpdateViewMatrix;
        bool shouldUpdateProjectionMatrix;
        Eigen::Matrix4f viewMatrix;
        Eigen::Matrix4f projectionMatrix;
        Eigen::Vector3f pos;

        float fov;
        float nearPanel;
        float farPanel;

        public:

        Camera();

        const Eigen::Matrix4f& getViewMatrix();
        const Eigen::Matrix4f& getProjectionMatrix();

        inline CameraBuffer getCameraBuffer(){
            return CameraBuffer{.viewMatrix = getViewMatrix(),.projectionMatrix = getProjectionMatrix()};
        }

        Eigen::Matrix4f calcViewMatrix()const;
        Eigen::Matrix4f calcProjectionMatrix()const;

        inline void setWidth(unsigned int width) {
            this->width = width;
            shouldUpdateProjectionMatrix = true;
        }

        inline void setHeight(unsigned int height) {
            this->height = height;
            shouldUpdateProjectionMatrix = true;
        }

        inline unsigned int getWidth() const{
            return width;
        }
        inline unsigned int getHeight() const{
            return height;
        }
    };
}