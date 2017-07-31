//
// Created by Administrator on 2017/7/26.
//

#include "CoordinateSystems.h"


void CoordinateSystems::InitGLes(int surfaceWidth, int surfaceHeight)
{
    m_render.Init(surfaceWidth, surfaceHeight);
}

void CoordinateSystems::OnDraw()
{
    m_render.Draw();
}

bool CoordinateSystems::Command(const Message& msg)
{
    return false;
}

void CoordinateSystems::Destroy()
{

}