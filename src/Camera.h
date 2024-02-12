#pragma once
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
namespace Chronos{

    struct CameraBuffer{
        Eigen::Matrix4f viewMatrix;
        Eigen::Matrix4f projectionMatrix;
    };
    /**
     * @brief 
     * 左手系
     */

    class Camera {

        private:
        unsigned int  width;
        unsigned int height;
        bool shouldUpdateViewMatrix;
        bool shouldUpdateProjectionMatrix;
        Eigen::Matrix4f viewMatrix;
        Eigen::Matrix4f projectionMatrix;

        Eigen::Vector3f pos;
        Eigen::Vector3f up;

        float yaw;
        float pitch;//角度
        float row;

        float fov;//角度
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

        inline void addYaw(float delta){
            yaw += delta;
            shouldUpdateViewMatrix = true;
        }
        inline void addPitch(float delta){
            pitch += delta;
            shouldUpdateViewMatrix = true;
        }

        inline unsigned int getWidth() const{
            return width;
        }
        inline unsigned int getHeight() const{
            return height;
        }
    };
}