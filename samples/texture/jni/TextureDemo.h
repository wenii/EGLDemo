//
// Created by Administrator on 2017/7/24.
//

#ifndef EGLDEMO_TEXTUREDEMO_H
#define EGLDEMO_TEXTUREDEMO_H
#include "AppInterface.h"
#include "Render.h"

class TextureDemo : public AppInterface
{
public:

    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    Render render;

};



#endif //EGLDEMO_TEXTUREDEMO_H
