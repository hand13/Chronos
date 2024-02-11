#include "Camera.h"
#include <Eigen/src/Core/Matrix.h>

namespace Chronos{

    Camera::Camera(){
            width = 0;
            height = 0;
            shouldUpdateViewMatrix = true;
            shouldUpdateProjectionMatrix = true;
            pos.x() = -0.5f;

            fov = 75.0;
            nearPanel = 0.1f;
            farPanel = 1.f;

    }

    const Eigen::Matrix4f& Camera::getViewMatrix(){
        if(shouldUpdateViewMatrix){
            viewMatrix = calcViewMatrix();
            shouldUpdateViewMatrix = false;
        }
        return viewMatrix;
    }
    const Eigen::Matrix4f& Camera::getProjectionMatrix(){
        if(shouldUpdateProjectionMatrix){
            projectionMatrix = calcProjectionMatrix();
            shouldUpdateProjectionMatrix = false;
        }
        return projectionMatrix;
    }

    Eigen::Matrix4f Camera::calcViewMatrix()const{
        Eigen::Matrix4f result;//列主序矩阵
            result << 
            1.f,0,0,-pos.x(),
            0,1.f,0,-pos.y(),
            0,0,1.f,-pos.z(),
            0,0,0,1.f;
        return result;
    }

    Eigen::Matrix4f Camera::calcProjectionMatrix()const{

        return Eigen::Matrix4f::Identity();
    } }