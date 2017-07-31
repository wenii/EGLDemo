//
// Created by Administrator on 2017/7/26.
//

#ifndef EGLDEMO_COORDINATESYSTEMS_H
#define EGLDEMO_COORDINATESYSTEMS_H

#include "AppInterface.h"
#include "Render.h"

class CoordinateSystems :public AppInterface
{
    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    Render m_render;
};



#endif //EGLDEMO_COORDINATESYSTEMS_H
