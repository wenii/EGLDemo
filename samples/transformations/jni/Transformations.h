//
// Created by Administrator on 2017/7/25.
//

#ifndef EGLDEMO_TRANSFORMATIONS_H
#define EGLDEMO_TRANSFORMATIONS_H

#include "AppInterface.h"

class Render;
class Transformations :public AppInterface
{
public:
    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    Render* m_render;
};



#endif //EGLDEMO_TRANSFORMATIONS_H
