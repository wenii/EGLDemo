//
// Created by Administrator on 2017/7/28.
//

#include "Camera.h"

Camera::Camera() :
    m_fov(45.0f),
    m_yaw(0.0f),
    m_pitch(0.0f),
    m_cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)),
    m_cameraFront(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_cameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{

}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(m_cameraPos, m_cameraFront, m_cameraUp);
}

void Camera::SetFov(float offset)
{
    const float range = 1000.0f;
    float newOffset = 45.0 * offset / range;

    if(m_fov >= 1.0f && m_fov <= 45.0f)
    {
        m_fov -= newOffset;
    }
    if(m_fov <= 1.0f)
    {
        m_fov = 1.0f;
    }
    if(m_fov >= 45.0f)
    {
        m_fov = 45.0f;
    }
}

void Camera::SetPos(float yawOffset, float pitchOffset)
{
    const float sensitivity = 0.1f;
    m_yaw -= yawOffset * sensitivity;
    m_pitch -= pitchOffset * sensitivity;

    if(m_pitch > 89.0f)
    {
        m_pitch = 89.0f;
    }
    if(m_pitch < -89.0f)
    {
        m_pitch = -89.0f;
    }

    glm::vec3 pos;
    pos.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    pos.y = sin(glm::radians(m_pitch));
    pos.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_cameraPos = glm::normalize(pos) * 3.0f;
}

