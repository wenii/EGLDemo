//
// Created by WWW on 2017/7/30.
//

#ifndef EGLDEMO_COLORS_H
#define EGLDEMO_COLORS_H

#include "AppInterface.h"
#include "Render.h"

class Colors : public AppInterface
{
public:

    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    void OnScroll(const Message& msg);
    void OnZoom(const Message& msg);

    Render render;
};



#endif //EGLDEMO_COLORS_H
