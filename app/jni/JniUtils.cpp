//
// Created by Administrator on 2017/7/21.
//

#include "JniUtils.h"

#include <stdio.h>
#include "Log.h"


void JniUtils::GetPackageCodePath(JNIEnv * jni, jclass activityClass, jobject activityObject, char* packageCodePath, int const maxLen)
{
	if ( packageCodePath == NULL || maxLen < 1 )
	{
		return;// packageCodePath;
	}

	packageCodePath[0] = '\0';

	jmethodID getPackageCodePathId = jni->GetMethodID( activityClass, "getPackageCodePath", "()Ljava/lang/String;" );
	if ( getPackageCodePathId == 0 )
	{
		LOGD( "Failed to find getPackageCodePath on class %llu, object %llu", (long long unsigned int)activityClass, (long long unsigned int)activityObject );
		return;// packageCodePath;
	}

	jstring jspath = (jstring)jni->CallObjectMethod( activityObject, getPackageCodePathId );
	if(jspath != NULL)
	{
	    const char* strPath = jni->GetStringUTFChars( jspath, NULL );
	    LOGD("JniUtils::GetPackageCodePath:path:%s", strPath);
	    sprintf(packageCodePath, "%s", strPath);

        jni->ReleaseStringUTFChars( jspath, strPath );
        jni->DeleteLocalRef( jspath );
	}
	else
	{
	    LOGD("GetPackageCodePath failed!!!!!");
	}

}