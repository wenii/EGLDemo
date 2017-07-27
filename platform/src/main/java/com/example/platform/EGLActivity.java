package com.example.platform;

import android.app.Activity;
import android.os.Bundle;
import android.support.v4.view.GestureDetectorCompat;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

/**
 * Created by WWW on 2017/7/23.
 */
public class EGLActivity extends Activity implements SurfaceHolder.Callback, View.OnTouchListener{

    public static native void nativeStart(long appPtr);
    public static native void nativePause(long appPtr);
    public static native void nativeStop(long appPtr);
    public static native void nativeSurfaceChanged(long appPtr, Surface surface, int width, int height);
    public static native void nativeSurfaceDestroy(long appPtr);
    public static native void nativeDestroy(long appPtr);
    public static native void nativeOnScroll(long appPtr, float benginX, float beginY, float endX, float endY, float distanceX, float distanceY);

    private static final String TAG = "EGLDemo";

    private SurfaceView surfaceView;
    protected long app;
    private GestureDetectorCompat mGestureDetector;


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

        mGestureDetector = new GestureDetectorCompat(this, new gestureListener());

        View view = surfaceView.getRootView();
        view.setOnTouchListener(this);
        view.setFocusable(true);
        view.setClickable(true);
        view.setLongClickable(true);

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
        app = 0;
    }

    @Override
    public boolean onTouch(View v, MotionEvent event)
    {
        Log.d(TAG, "onTouch");
        return mGestureDetector.onTouchEvent(event);
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

    private class gestureListener implements GestureDetector.OnGestureListener{


        public boolean onDown(MotionEvent e)
        {
            Log.i(TAG, "onDown");
            return false;
        }

        public void onShowPress(MotionEvent e)
        {
            Log.i(TAG, "onShowPress");
        }

        public boolean onSingleTapUp(MotionEvent e)
        {
            Log.i(TAG, "onSingleTapUp");
            return true;
        }

        public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY)
        {
            Log.i(TAG, "onScroll:" + "e1.getX():" + e1.getX() + "--e2.getX()" + e2.getX() +"--distanceX: "+distanceX + "--distanceY:" + distanceY);
            nativeOnScroll(app, e1.getX(), e1.getY(), e2.getX(), e2.getY(), distanceX, distanceY);
            return true;
        }

        public void onLongPress(MotionEvent e)
        {
            Log.i(TAG, "onLongPress");
        }

        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY)
        {
            Log.i(TAG, "onFling");
            return true;
        }
    };
}
