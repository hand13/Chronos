#pragma once
#include <Eigen/Eigen>
#include <Eigen/src/Core/Matrix.h>
#include "Utils.h"
namespace Chronos{

    struct CameraBuffer{
        Eigen::Matrix4f viewMatrix;
        Eigen::Matrix4f projectionMatrix;
    };
    /**
     * @brief 
     * 世界默认z朝上左手系,view 左手系
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
        inline Float3 getPos(){
            return Float3(pos.x(),pos.y(),pos.z());
        }

        void addYaw(float delta);
        void addPitch(float delta);
        void moveForward(float delta);
        void moveRight(float delta);

        Eigen::Vector3f getDirection()const;
        Eigen::Vector3f getRight()const;
        inline unsigned int getWidth() const{
            return width;
        }
        inline unsigned int getHeight() const{
            return height;
        }
    };
}