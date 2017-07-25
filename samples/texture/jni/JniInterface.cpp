//
// Created by Administrator on 2017/7/24.
//


#include <jni.h>
#include <android/native_window_jni.h>
#include "TextureDemo.h"

extern "C"

{
    long Java_com_example_texture_MainActivity_nativeSetAppInterface(JNIEnv* jni, jclass clazz, jobject obj)
    {
        return (long)((new TextureDemo())->SetActivity(jni, obj));
    }

} //extern "C"