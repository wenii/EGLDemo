//
// Created by Administrator on 2017/7/24.
//

#include "TextureDemo.h"


void TextureDemo::InitGLes(int surfaceWidth, int surfaceHeight)
{
    render.Init(surfaceWidth, surfaceHeight);
}

void TextureDemo::OnDraw()
{
    render.Draw();
}

bool TextureDemo::Command(const Message& msg)
{
    return false;
}

void TextureDemo::Destroy()
{

}