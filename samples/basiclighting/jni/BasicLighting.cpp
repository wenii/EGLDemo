//
// Created by WWW on 2017/8/1.
//

#include "BasicLighting.h"


#include "MessageQueue.h"
#include "Log.h"


void BasicLighting::InitGLes(int surfaceWidth, int surfaceHeight)
{
    m_render.Init(surfaceWidth, surfaceHeight);
}

void BasicLighting::OnDraw()
{
    m_render.Draw();
}

bool BasicLighting::Command(const Message& msg)
{
    switch(msg.GetType())
    {
        case MESSAGE_ON_GESTURE_SCROLL:
            OnScroll(msg);
            break;
        case MESSAGE_ON_GESTURE_ZOOM:
            OnZoom(msg);
            break;
        default:
            break;
    }
    return false;
}

void BasicLighting::Destroy()
{

}

void BasicLighting::OnScroll(const Message& msg)
{
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
    m_render.SetYawPatch(distanceX, distanceY);
}

void BasicLighting::OnZoom(const Message& msg)
{
    float oldDistance = 0.0f;
    float newDistance = 0.0f;
    msg.GetParam(MSG_CONTENT_GESTURE_ZOOM_OLD_DISTANCE, oldDistance);
    msg.GetParam(MSG_CONTENT_GESTURE_ZOOM_NEW_DISTANCE, newDistance);

    LOGD("Camera::Command:OnZoom:oldDistance:%f, newDistance:%f", oldDistance, newDistance);

    float offset = newDistance - oldDistance;
    m_render.SetZoomParam(offset);
}
