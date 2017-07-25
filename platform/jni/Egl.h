//
// Created by Administrator on 2017/7/19.
//

#ifndef EGLTEST_EGL_H
#define EGLTEST_EGL_H
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>


class Egl
{
public:
    Egl();
    void Clear();
    void CreateContext();
    void DestroyContext();
    bool CreateSurface(ANativeWindow * nativeWindow);
    void DestroySurface();
    void SwapBuffers();

public:
	EGLint		MajorVersion;
	EGLint		MinorVersion;
	EGLDisplay	Display;
	EGLConfig	Config;
	EGLSurface	Surface;
	EGLContext	Context;

};



#endif //EGLTEST_EGL_H
