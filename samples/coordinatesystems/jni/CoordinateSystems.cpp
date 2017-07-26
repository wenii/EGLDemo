//
// Created by Administrator on 2017/7/26.
//

#include "CoordinateSystems.h"


void CoordinateSystems::InitGLes(int surfaceWidth, int surfaceHeight)
{
    render.Init(surfaceWidth, surfaceHeight);
}

void CoordinateSystems::OnDraw()
{
    render.Draw();
}

bool CoordinateSystems::Command(const Message& msg)
{
    return false;
}

void CoordinateSystems::Destroy()
{

}