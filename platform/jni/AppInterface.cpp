//
// Created by Administrator on 2017/7/24.
//

#include "AppInterface.h"
#include "App.h"


AppInterface::AppInterface()
{

}

AppInterface::~AppInterface()
{

}

void AppInterface::InitGLes(int surfaceWidth, int surfaceHeight)
{
    //render.Init(surfaceWidth, surfaceHeight);
}

void AppInterface::OnDraw()
{
    //render.Draw();
}

bool AppInterface::Command(const Message& msg)
{
    return false;
}
void AppInterface::Destroy()
{

}

App* AppInterface::SetActivity(JNIEnv* jni, jobject activityObject)
{
    return new App(this, jni, activityObject);
}
