package com.example.transformations;

import android.os.Bundle;
import com.example.framework.EGLActivity;

public class MainActivity extends EGLActivity {

    static {
        System.loadLibrary("transformations");
    }

    public static native long nativeSetAppInterface(EGLActivity activity);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        app = nativeSetAppInterface(MainActivity.this);
    }
}
