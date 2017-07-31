//
// Created by Administrator on 2017/7/18.
//

#ifndef EGLTEST_APP_H
#define EGLTEST_APP_H
#include <pthread.h>
#include <android/native_window_jni.h>
#include "Egl.h"

class MessageQueue;
class Message;
class AppInterface;
class App
{
public:
    App(AppInterface* interface, JNIEnv* jni, jobject activityObject);
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

public:
    pthread_t           m_threadId;
    bool                m_bStartRender;
    bool                m_bSetSurface;
    bool                m_bDestroy;

    Egl*                m_egl;
    MessageQueue*       m_msgQueue;
    ANativeWindow*      m_nativeWindow;
    AppInterface*       m_interface;

    JNIEnv*             m_jni;
    jobject             m_javaObject;
    jclass	            m_activityClass;



};



#endif //EGLTEST_APP_H
