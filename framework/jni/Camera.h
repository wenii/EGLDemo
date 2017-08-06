//
// Created by Administrator on 2017/7/28.
//

#ifndef EGLDEMO_CAMERA_H
#define EGLDEMO_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera {

public:
    Camera();

    glm::mat4 GetViewMatrix();
    float GetFov(){return m_fov;}
    void SetFov(float offset);
    void SetPos(float yawOffset, float pitchOffset);

private:
    float       m_fov;
    float       m_yaw;
    float       m_pitch;
public:
    glm::vec3   m_cameraPos;
    glm::vec3   m_cameraFront;
    glm::vec3   m_cameraUp;


};



#endif //EGLDEMO_CAMERA_H
