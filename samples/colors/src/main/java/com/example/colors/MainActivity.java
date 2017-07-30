package com.example.colors;

import android.os.Bundle;
import com.example.platform.EGLActivity;

public class MainActivity extends EGLActivity {

    static {
        System.loadLibrary("colors");
    }

    public static native long nativeSetAppInterface(EGLActivity activity);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app = nativeSetAppInterface(MainActivity.this);
    }
}
