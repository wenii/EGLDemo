//
// Created by Administrator on 2017/7/19.
//

#include "Egl.h"
#include "Log.h"



Egl::Egl()
{
    Clear();
}

void Egl::Clear()
{
	MajorVersion = 0;
	MinorVersion = 0;
	Config = 0;
	Display = EGL_NO_DISPLAY;
	Surface = EGL_NO_SURFACE;
	Context = EGL_NO_CONTEXT;
}

void Egl::CreateContext()
{
    if(Display != EGL_NO_DISPLAY)
    {
        LOGD("Display != 0");
        return;
    }

    Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if(Display == EGL_NO_DISPLAY || eglGetError() != EGL_SUCCESS)
    {
        LOGD("CreateContext:ERROR:eglGetDisplay failed!");
        return;
    }

    EGLBoolean elgInitRetState = eglInitialize(Display, &MajorVersion, &MinorVersion);
    if(elgInitRetState == EGL_FALSE || eglGetError() != EGL_SUCCESS)
    {
        LOGD("CreateContext:ERROR:eglInitialize failed!");
        return;
    }
    LOGD("CreateContext->MajorVersion:%d, MinorVersion:%d", MajorVersion, MinorVersion);

	const EGLint configAttribs[] =
	{
		EGL_ALPHA_SIZE, 8,
		EGL_BLUE_SIZE,  8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE,   8,
		EGL_DEPTH_SIZE, 8,
		EGL_SAMPLES,	0,
		EGL_NONE
	};

	EGLint numConfigs;
    EGLConfig config;

	EGLBoolean eglChooseConfigState = eglChooseConfig(Display, configAttribs, &Config, 1, &numConfigs);
	if(eglChooseConfigState == EGL_FALSE || eglGetError() != EGL_SUCCESS)
	{
	    LOGD("CreateContext:ERROR:eglChooseConfig failed!");
	    return;
	}

	EGLint contextAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 3,
		EGL_NONE
	};

	Context = eglCreateContext( Display, Config, EGL_NO_CONTEXT, contextAttribs );
	LOGD("CreateContext:Succeed!");

}

void Egl::DestroyContext()
{
	if ( Display != EGL_NO_DISPLAY )
	{
		if ( eglMakeCurrent( Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT ) == EGL_FALSE )
		{
            LOGD("DestroyContext:eglMakeCurrent failed!error:%d", eglGetError());
		}
	}
	if ( Context != EGL_NO_CONTEXT )
	{
		if ( eglDestroyContext( Display, Context ) == EGL_FALSE )
		{
            LOGD("DestroyContext:eglDestroyContext failed!error:%d", eglGetError());
		}
		Context = EGL_NO_CONTEXT;
	}
	if ( Display != EGL_NO_DISPLAY )
	{
		if ( eglTerminate( Display ) == EGL_FALSE )
		{
		    LOGD("DestroyContext:eglTerminate failed!error:%d", eglGetError());
		}
		Display = EGL_NO_DISPLAY;
	}
}

//要在当前线程里面干这件事
bool Egl::CreateSurface(ANativeWindow * nativeWindow)
{
	if ( Surface != EGL_NO_SURFACE || Display == EGL_NO_DISPLAY )
	{
		return false;
	}
	const EGLint surfaceAttribs[] = {EGL_NONE};
	Surface = eglCreateWindowSurface( Display, Config, nativeWindow, surfaceAttribs );
	if ( Surface == EGL_NO_SURFACE )
	{
		LOGD("CreateSurface:ERROR:eglCreateWindowSurface failed!Error:%d", eglGetError());
		return false;
	}
	if ( eglMakeCurrent( Display, Surface, Surface, Context ) == EGL_FALSE )
	{
		LOGD("CreateSurface:ERROR:eglMakeCurrent failed!Error:%d", eglGetError());
		return false;
	}

	LOGD("CreateSurface Succeed!");
	return true;
}

void Egl::DestroySurface()
{
	if ( Surface != EGL_NO_SURFACE )
	{
		if ( eglDestroySurface( Display, Surface ) == EGL_FALSE )
		{
		    LOGD("DestroySurface:eglDestroySurface failed!error:%d", eglGetError());
		}
		Surface = EGL_NO_SURFACE;
	}
}

void Egl::SwapBuffers()
{
    if(eglSwapBuffers(Display, Surface) == EGL_FALSE)
    {
        LOGD("eglSwapBuffers failed!error:%d", eglGetError());
    }
}