package com.example.texture;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import com.example.platform.EGLActivity;

public class MainActivity extends EGLActivity{

    static {
        System.loadLibrary("texture");
    }

    public static native long nativeSetAppInterface(EGLActivity activity);

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        app = nativeSetAppInterface(MainActivity.this);
    }

}