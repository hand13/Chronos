#include "Camera.h"
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/Core/util/ForwardDeclarations.h>
#include <cmath>

namespace Chronos{

    Camera::Camera(){
            width = 0;
            height = 0;
            shouldUpdateViewMatrix = true;
            shouldUpdateProjectionMatrix = true;

            pos.x() = 0.2f;
            pos.z() =-4.f;
            up = {0,1.f,0};
            fov = 75.0;
            nearPanel = 0.1f;
            farPanel = 1000.f;

            yaw = 0.f;
            pitch = 0.f;

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

        float tmpYaw = yaw/180.0 * 3.14;
        float tmpPitch = pitch/180.0 * 3.14;

        Eigen::Vector3f zAxis; 

        zAxis  << sin(tmpYaw)*cos(tmpPitch),sin(tmpPitch)
        ,cos(tmpYaw) *cos(tmpYaw);//direction

        Eigen::Vector3f xAxis = up.cross(zAxis);
        Eigen::Vector3f yAxis = zAxis.cross(xAxis);

        Eigen::Matrix3f tmp;
        tmp << 
        xAxis.x(),yAxis.x(),zAxis.x(),
        xAxis.y(),yAxis.y(),zAxis.y(),
        xAxis.z(),yAxis.z(),zAxis.z();

        Eigen::Matrix3f it = tmp.inverse();


        Eigen::Matrix4f result;//列主序矩阵
            result << 
            1.f,0,0,-pos.x(),
            0,1.f,0,-pos.y(),
            0,0,1.f,-pos.z(),
            0,0,0,1.f;
        Eigen::Matrix4f angleMatrix;

        angleMatrix <<
        it(0,0),it(0,1),it(0,2),0,
        it(1,0),it(1,1),it(1,2),0,
        it(2,0),it(2,1),it(2,2),0,
        0,0,0,1.f;

        // Eigen::Matrix4f yawMatrix;

        // yawMatrix <<
        //     cos(tmpYaw),0,sin(tmpYaw),0,
        //     0,1.f,0,0,
        //     -sin(tmpYaw),0,cos(tmpYaw),0,
        //     0,0,0,1.f;

        // Eigen::Matrix4f pitchMatrix;


        return angleMatrix * result;
        // return Eigen::Matrix4f::Identity();
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