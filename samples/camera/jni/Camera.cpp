//
// Created by Administrator on 2017/7/27.
//

#include "Camera.h"
#include "MessageQueue.h"
#include "Log.h"

void Camera::InitGLes(int surfaceWidth, int surfaceHeight)
{
    render.Init(surfaceWidth, surfaceHeight);
}

void Camera::OnDraw()
{
    render.Draw();
}

bool Camera::Command(const Message& msg)
{
    LOGD("Camera::Command");
    float beginX = 0.0f;
    float beginY = 0.0f;
    float endX = 0.0f;
    float endY = 0.0f;
    float distanceX = 0.0f;
    float distanceY = 0.0f;
    msg.GetParam(MSG_CONTENT_GESTURE_BEGIN_X, beginX);
    msg.GetParam(MSG_CONTENT_GESTURE_BEGIN_Y, beginY);
    msg.GetParam(MSG_CONTENT_GESTURE_END_X, endX);
    msg.GetParam(MSG_CONTENT_GESTURE_END_Y, endY);
    msg.GetParam(MSG_CONTENT_GESTURE_DISTANCE_X, distanceX);
    msg.GetParam(MSG_CONTENT_GESTURE_DISTANCE_Y, distanceY);
    LOGD("Camera::Command:beginX:%f--beginY:%f--endX:%f--endY:%f--distanceX:%f--distanceY:%f",
        beginX, beginY, endX, endY, distanceX, distanceY);
    render.SetYawPatch(distanceX, distanceY);
    return false;
}

void Camera::Destroy()
{

}