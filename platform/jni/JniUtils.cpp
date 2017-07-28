//
// Created by Administrator on 2017/7/21.
//

#include "JniUtils.h"

#include <stdio.h>
#include "Log.h"
#include "App.h"
#include "MessageQueue.h"

extern "C"
{
    void Java_com_example_platform_EGLActivity_nativeStart(JNIEnv* jni, jclass clazz, jlong appPtr)
    {
        LOGD("nativeStart!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            app->Start();
        }
    }

    void Java_com_example_platform_EGLActivity_nativePause(JNIEnv* jni, jclass clazz, jlong appPtr)
    {
        LOGD("nativePause!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_PAUSE);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_platform_EGLActivity_nativeStop(JNIEnv* jni, jclass clazz, jlong appPtr)
    {
        LOGD("nativeStop!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_STOP);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_platform_EGLActivity_nativeSurfaceChanged(JNIEnv* jni, jclass clazz, jlong appPtr, jobject surface, jint width, jint height)
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
                msg.SetParam(MSG_CONTENT_SURFACE_WIDTH, width);
                msg.SetParam(MSG_CONTENT_SURFACE_HEIGHT, height);
                app->m_msgQueue->PostMessage(msg);
            }
            else
            {
                ANativeWindow_release( newNativeWindow );
            }
        }
    }

    void Java_com_example_platform_EGLActivity_nativeSurfaceDestroy(JNIEnv* jni, jclass clazz, jlong appPtr)
    {
        LOGD("nativeSurfaceDestroy!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_SURFACE_DESTROY);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_platform_EGLActivity_nativeDestroy(JNIEnv* jni, jclass clazz, jlong appPtr)
    {
        LOGD("nativeActiveDestroy!");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_ACTIVITY_DESTROY);
            app->m_msgQueue->PostMessage(msg);
        }
    }

    void Java_com_example_platform_EGLActivity_nativeOnScroll(JNIEnv* jni, jclass clazz, jlong appPtr, jfloat benginX, jfloat beginY, jfloat endX, jfloat endY, jfloat distanceX, jfloat distanceY)
    {
        LOGD("nativeOnScroll");
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_GESTURE_SCROLL);
            msg.SetParam(MSG_CONTENT_GESTURE_BEGIN_X, benginX);
            msg.SetParam(MSG_CONTENT_GESTURE_BEGIN_Y, beginY);
            msg.SetParam(MSG_CONTENT_GESTURE_END_X, endX);
            msg.SetParam(MSG_CONTENT_GESTURE_END_Y, endY);
            msg.SetParam(MSG_CONTENT_GESTURE_DISTANCE_X, distanceX);
            msg.SetParam(MSG_CONTENT_GESTURE_DISTANCE_Y, distanceY);
            app->m_msgQueue->PostMessage(msg);
            LOGD("nativeOnScroll msg send ok...");
        }
    }

    void Java_com_example_platform_EGLActivity_nativeOnZoom(JNIEnv* jni, jclass clazz, jlong appPtr, jfloat oldDistance, jfloat newDistance)
    {
        App* app = (App*)appPtr;
        if(app != NULL)
        {
            Message msg(MESSAGE_ON_GESTURE_ZOOM);
            msg.SetParam(MSG_CONTENT_GESTURE_ZOOM_OLD_DISTANCE, oldDistance);
            msg.SetParam(MSG_CONTENT_GESTURE_ZOOM_NEW_DISTANCE, newDistance);
            app->m_msgQueue->PostMessage(msg);
        }
    }

} //extern "C"

void JniUtils::GetPackageCodePath(JNIEnv * jni, jclass activityClass, jobject activityObject, char* packageCodePath, int const maxLen)
{
	if ( packageCodePath == NULL || maxLen < 1 )
	{
		return;// packageCodePath;
	}

	packageCodePath[0] = '\0';

	jmethodID getPackageCodePathId = jni->GetMethodID( activityClass, "getPackageCodePath", "()Ljava/lang/String;" );
	if ( getPackageCodePathId == 0 )
	{
		LOGD( "Failed to find getPackageCodePath on class %llu, object %llu", (long long unsigned int)activityClass, (long long unsigned int)activityObject );
		return;// packageCodePath;
	}

	jstring jspath = (jstring)jni->CallObjectMethod( activityObject, getPackageCodePathId );
	if(jspath != NULL)
	{
	    const char* strPath = jni->GetStringUTFChars( jspath, NULL );
	    LOGD("JniUtils::GetPackageCodePath:path:%s", strPath);
	    sprintf(packageCodePath, "%s", strPath);

        jni->ReleaseStringUTFChars( jspath, strPath );
        jni->DeleteLocalRef( jspath );
	}
	else
	{
	    LOGD("GetPackageCodePath failed!!!!!");
	}

}