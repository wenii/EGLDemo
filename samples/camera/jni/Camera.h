//
// Created by Administrator on 2017/7/27.
//

#ifndef EGLDEMO_CAMERA_H
#define EGLDEMO_CAMERA_H

#include "AppInterface.h"
#include "Render.h"

class Camera : public AppInterface
{
    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    Render render;
};



#endif //EGLDEMO_CAMERA_H
