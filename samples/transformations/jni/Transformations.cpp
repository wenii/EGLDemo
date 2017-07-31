//
// Created by Administrator on 2017/7/25.
//

#include "Transformations.h"

#include "Render.h"

void Transformations::InitGLes(int surfaceWidth, int surfaceHeight)
{
    m_render = new Render;
    m_render->Init(surfaceWidth, surfaceHeight);
}

void Transformations::OnDraw()
{
    m_render->Draw();
}

bool Transformations::Command(const Message& msg)
{
    return false;
}

void Transformations::Destroy()
{

}

