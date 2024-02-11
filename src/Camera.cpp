#include "Camera.h"
#include <Eigen/src/Core/Matrix.h>
#include <cmath>

namespace Chronos{

    Camera::Camera(){
            width = 0;
            height = 0;
            shouldUpdateViewMatrix = true;
            shouldUpdateProjectionMatrix = true;
            pos.x() = 0.f;
            pos.z() =-2.f;
            fov = 75.0;
            nearPanel = 0.1f;
            farPanel = 1000.f;

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
    /**
     * @brief 
     * z near~far => 0~1
     * @return Eigen::Matrix4f 
     */

    Eigen::Matrix4f Camera::calcProjectionMatrix()const{

        float hw = static_cast<float>(height)/static_cast<float>(width);
        float w = 2.f * nearPanel * tan(fov/360.f * 3.14f);
        float h = hw * w;
        float a = farPanel /(farPanel - nearPanel);
        float b = (farPanel * nearPanel)/(nearPanel - farPanel);
        Eigen::Matrix4f resut;
        resut <<
        2.f* nearPanel/w,0,0,0,
        0,2.f*nearPanel/h,0,0,
        0,0,a,b,
        0,0,1.f,0;
        return resut;
        // return Eigen::Matrix4f::Identity();
    } 
}