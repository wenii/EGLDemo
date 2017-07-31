//
// Created by Administrator on 2017/7/27.
//

#ifndef EGLDEMO_CAMERADEMO_H
#define EGLDEMO_CAMERADEMO_H

#include "AppInterface.h"
#include "Render.h"

class CameraDemo : public AppInterface
{
private:
    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    void OnScroll(const Message& msg);
    void OnZoom(const Message& msg);

    Render m_render;
};



#endif //EGLDEMO_CAMERA_H
