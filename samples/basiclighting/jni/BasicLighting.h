//
// Created by WWW on 2017/8/1.
//

#ifndef EGLDEMO_BASICLIGHTING_H
#define EGLDEMO_BASICLIGHTING_H

#include "AppInterface.h"
#include "Render.h"

class BasicLighting : public AppInterface
{
public:

    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    void OnScroll(const Message& msg);
    void OnZoom(const Message& msg);

    Render m_render;

};



#endif //EGLDEMO_BASICLIGHTING_H
