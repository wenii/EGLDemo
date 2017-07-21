//
// Created by WWW on 2017/7/18.
//

#include <jni.h>
#include "App.h"
#include <android/native_window_jni.h>
#include "Log.h"
#include <pthread.h>
#include "MessageQueue.h"
extern "C"
{
    long Java_com_example_administrator_egldemo_MainActivity_nativeSetApp(JNIEnv* jni, jobject obj)
    {
        return (long)(new App(jni, obj));
    }


    void Java_com_example_administrator_egldemo_MainActivity_nativeStart(JNIEnv* jni, jobject obj, long appPtr)
    {
        LOGD("nativeStart!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            app->Start();
        }
    }

    void Java_com_example_administrator_egldemo_MainActivity_nativePause(JNIEnv* jni, jobject obj, long appPtr)
    {
        LOGD("nativePause!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_PAUSE);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_administrator_egldemo_MainActivity_nativeStop(JNIEnv* jni, jobject obj, long appPtr)
    {
        LOGD("nativeStop!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_STOP);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_administrator_egldemo_MainActivity_nativeSurfaceChanged(JNIEnv* jni, jobject obj, long appPtr, jobject surface)
    {
        LOGD("nativeSurfaceChanged!");
        ANativeWindow * newNativeWindow = ANativeWindow_fromSurface( jni, surface );
        App* app = (App*)appPtr;

        if(app != NULL)
        {
            if(app->m_nativeWindow != newNativeWindow)
            {   if(app->m_nativeWindow != NULL)
                {
                    ANativeWindow_release( app->m_nativeWindow );
                }
                Message msg(MESSAGE_ON_SURFACE_CHANGED);
                msg.SetParam(MSG_CONTENT_ANATIVEWINDOW, newNativeWindow);
                app->m_msgQueue->PostMessage(msg);
            }
            else
            {
                ANativeWindow_release( newNativeWindow );
            }
        }
    }

    void Java_com_example_administrator_egldemo_MainActivity_nativeSurfaceDestroy(JNIEnv* jni, jobject obj, long appPtr)
    {
        LOGD("nativeSurfaceDestroy!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_SURFACE_DESTROY);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_administrator_egldemo_MainActivity_nativeDestroy(JNIEnv* jni, jobject obj, long appPtr)
    {
        LOGD("nativeActiveDestroy!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_DESTROY);
            app->m_msgQueue->PostMessage(msg);
        }


    }

} //extern "C"