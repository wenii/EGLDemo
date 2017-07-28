//
// Created by Administrator on 2017/7/24.
//


#include <jni.h>
#include <android/native_window_jni.h>
#include "CameraDemo.h"

extern "C"

{
    long Java_com_example_camera_MainActivity_nativeSetAppInterface(JNIEnv* jni, jclass clazz, jobject obj)
    {
        return (long)((new CameraDemo())->SetActivity(jni, obj));
    }

} //extern "C"