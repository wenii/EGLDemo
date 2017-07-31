//
// Created by Administrator on 2017/7/21.
//

#ifndef EGLDEMO_JNIUTILS_H
#define EGLDEMO_JNIUTILS_H

#include "jni.h"

class JniUtils
{

public:
    static void GetPackageCodePath(JNIEnv * jni, jclass activityClass, jobject activityObject, char * packageCodePath, int const maxLen);

};



#endif //EGLDEMO_JNIUTILS_H
