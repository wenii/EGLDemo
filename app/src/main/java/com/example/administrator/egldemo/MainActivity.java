package com.example.administrator.egldemo;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Window;

public class MainActivity extends Activity implements SurfaceHolder.Callback{

    static {
        System.loadLibrary("EGLDemo");
    }

    private static final String TAG = "EGLDemo";

    private SurfaceView surfaceView;
    private long app;

    public native long nativeSetApp();
    public native void nativeStart(long appPtr);
    public native void nativePause(long appPtr);
    public native void nativeStop(long appPtr);
    public native void nativeSurfaceChanged(long appPtr, Surface surface, int width, int height);
    public native void nativeSurfaceDestroy(long appPtr);
    public native void nativeDestroy(long appPtr);

    public String getPackageCodePath()
    {
        Log.d(TAG, "getPackageCodePath");
        return getApplicationContext().getPackageCodePath();
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        surfaceView = new SurfaceView(this);
        surfaceView.getHolder().addCallback(this);

        setContentView(surfaceView);

        app = nativeSetApp();
    }

    @Override
    public void onStart()
    {
        Log.d(TAG, "onStart");
        super.onStart();
        nativeStart(app);
    }

    @Override
    public void onResume() {
        Log.d(TAG, "onResume");
        super.onResume();
    }

    @Override
    public void onPause()
    {
        Log.d(TAG, "onPause");
        super.onPause();
        nativePause(app);
    }

    @Override
    public void onStop()
    {
        Log.d(TAG, "onStop");
        super.onStop();
        nativeStop(app);
    }

    @Override
    public void onDestroy()
    {
        Log.d(TAG, "onDestroy");
        super.onDestroy();
        nativeDestroy(app);
    }



    @Override
    public void surfaceCreated(SurfaceHolder holder)
    {
        Log.d(TAG, "surfaceCreate");
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
    {
        Log.d(TAG, "surfaceChanged");
        nativeSurfaceChanged(app, holder.getSurface(), width, height);

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {
        Log.d(TAG, "surfaceDestroyed");
        nativeSurfaceDestroy(app);
    }
}
