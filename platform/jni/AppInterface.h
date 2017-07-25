//
// Created by Administrator on 2017/7/24.
//

#ifndef EGLDEMO_APPINTERFACE_H
#define EGLDEMO_APPINTERFACE_H
#include <jni.h>
class App;
class Message;

class AppInterface
{
public:
    AppInterface();
    virtual ~AppInterface();

    virtual void InitGLes(int surfaceWidth, int surfaceHeight);
    virtual void OnDraw();
    virtual bool Command(const Message& msg);
    virtual void Destroy();

    App* SetActivity(JNIEnv* jni, jobject activityObject);

    //test
    //Render render;
    //end

public:
    App* app;
};



#endif //EGLDEMO_APPINTERFACE_H
