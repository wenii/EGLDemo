//
// Created by Administrator on 2017/7/18.
//

#include "App.h"
#include "Log.h"
#include <unistd.h>
#include "MessageQueue.h"
#include "JniUtils.h"
#include "PackageFiles.h"
#include "AppInterface.h"


static const char* activityClassName = "com/example/platform/EGLActivity";


App::App(AppInterface* interface, JNIEnv* jni, jobject activityObject)
{
    interface->app = this;
    Interface = interface;

    m_nativeWindow = NULL;
    m_bStartRender = false;
    m_bSetSurface = false;
    m_bDestroy = false;
    this->jni = jni;

    javaObject = jni->NewGlobalRef( activityObject);

    jclass lc = jni->FindClass(activityClassName);
    if ( lc != 0 )
    {
    	ActivityClass = (jclass)jni->NewGlobalRef( lc );
    }
    jni->DeleteLocalRef( lc );

    char apkPath[1024];
    JniUtils::GetPackageCodePath( jni, ActivityClass, javaObject, apkPath, sizeof( apkPath ) );
    LOGD("apkPath:%s", apkPath);

    PackageFiles::SetZipFilePath(apkPath);

}

App::~App()
{
    m_egl->DestroyContext();

    delete m_egl;
    m_egl = NULL;

    delete m_msgQueue;
    m_msgQueue = NULL;

    delete Interface;
    Interface = NULL;

}

void App::Start()
{
    const int ret = pthread_create(&m_threadId, NULL, Callback, this);
    if(ret != 0)
    {
        LOGD("pthread_create failed!");
    }
}

void* App::Callback(void* param)
{
    App* app = (App*)param;
    app->ThreadFun();
    delete app;
    app = NULL;
}

void App::ThreadFun()
{
    m_egl = new Egl;
    m_egl->CreateContext();

    m_msgQueue = new MessageQueue;

    m_bDestroy = false;

    while(!m_bDestroy)
    {
        //LOGD("loop!");
        ProcessEvent();
        //sleep(1);

        if(m_bStartRender)
        {
            //LOGD("Draw");
            Interface->OnDraw();
            m_egl->SwapBuffers();
        }

    }

}

void App::ProcessEvent()
{
    Message msg;
    if(m_msgQueue->GetNextMessage(msg))
    {
        LOGD("App::ProcessEvent");
        switch(msg.GetType())
        {
            case MESSAGE_ON_SURFACE_CHANGED:
                LOGD("App::ProcessEvent:MESSAGE_ON_SURFACE_CHANGED");
                OnSurfaceChanged(msg);
                break;
            case MESSAGE_ON_SURFACE_DESTROY:
                LOGD("App::ProcessEvent:MESSAGE_ON_SURFACE_DESTROY");
                OnSurfaceDestroy();
                break;
            case MESSAGE_ON_ACTIVITY_PAUSE:
                LOGD("App::ProcessEvent:MESSAGE_ON_ACTIVITY_PAUSE");
                OnActivityPause();
                break;
            case MESSAGE_ON_ACTIVITY_STOP:
                LOGD("App::ProcessEvent:MESSAGE_ON_ACTIVITY_STOP");
                OnActivityStop();
                break;
            case MESSAGE_ON_ACTIVITY_DESTROY:
                LOGD("App::ProcessEvent:MESSAGE_ON_ACTIVITY_DESTROY");
                OnActivityDestroy();
                break;
            case MESSAGE_ON_GESTURE_SCROLL:
            case MESSAGE_ON_GESTURE_ZOOM:
                LOGD("App::ProcessEvent:MESSAGE_ON_GESTURE_SCROLL");
                Interface->Command(msg);
            default:
                LOGD("app::ProcessEvent:error type!");
                break;
        }
    }
}

void App::OnSurfaceChanged(const Message& msg)
{
    void* newNativeWindow = NULL;
    if(msg.GetParam(MSG_CONTENT_ANATIVEWINDOW, newNativeWindow) && newNativeWindow != NULL)
    {
        LOGD("App::OnSurfaceChanged set newNativeWindow");
        m_nativeWindow = (ANativeWindow*)newNativeWindow;
        if(m_egl->CreateSurface(m_nativeWindow))
        {
            int width = 0;
            int height = 0;
            msg.GetParam(MSG_CONTENT_SURFACE_WIDTH, width);
            msg.GetParam(MSG_CONTENT_SURFACE_HEIGHT, height);
            Interface->InitGLes(width, height);
            m_bStartRender = true;
        }
    }
}

void App::OnSurfaceDestroy()
{
    m_egl->DestroySurface();
    m_bStartRender = false;
}

void App::OnActivityPause()
{
    m_bStartRender = false;
}

void App::OnActivityStop()
{
    m_bStartRender = false;
}

void App::OnActivityDestroy()
{
    m_bDestroy = true;
    Interface->Destroy();
}