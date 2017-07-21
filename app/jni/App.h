//
// Created by Administrator on 2017/7/18.
//

#ifndef EGLTEST_APP_H
#define EGLTEST_APP_H
#include <pthread.h>
#include <android/native_window_jni.h>
#include "Egl.h"

class Render;
class MessageQueue;
class Message;
class PackageFiles;
class App
{
public:
    pthread_t           m_threadId;
    bool                m_bStartRender;
    bool                m_bSetSurface;
    bool                m_bDestroy;

    Egl* m_egl;
    Render* m_render;
    MessageQueue* m_msgQueue;
    //PackageFiles* m_packageFiles;
    ANativeWindow* m_nativeWindow;

    JNIEnv* jni;
    jobject javaObject;
    jclass	ActivityClass;

public:
    App(JNIEnv* jni, jobject activityObject);
    ~App();
    void Start();

private:
    static void* Callback(void* param);
    void ThreadFun();

    void ProcessEvent();
    void OnSurfaceChanged(const Message& msg);
    void OnSurfaceDestroy();
    void OnActivityPause();
    void OnActivityStop();
    void OnActivityDestroy();



};



#endif //EGLTEST_APP_H
