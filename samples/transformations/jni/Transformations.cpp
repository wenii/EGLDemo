//
// Created by Administrator on 2017/7/25.
//

#include "Transformations.h"

#include "Render.h"

void Transformations::InitGLes(int surfaceWidth, int surfaceHeight)
{
    render = new Render;
    render->Init(surfaceWidth, surfaceHeight);
}

void Transformations::OnDraw()
{
    render->Draw();
}

bool Transformations::Command(const Message& msg)
{
    return false;
}

void Transformations::Destroy()
{

}

