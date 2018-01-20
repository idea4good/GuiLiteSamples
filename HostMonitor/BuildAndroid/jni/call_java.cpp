#include <jni.h>
#include <android/log.h>

JavaVM* javaVM = 0;
jclass activityClass;
void InitJavaEnv(JNIEnv* env, jobject obj)
{
    env->GetJavaVM(&javaVM);
    jclass cls = env->GetObjectClass(obj);
    activityClass = (jclass) env->NewGlobalRef(cls);
}

void OnAndroidPlayWav(const char* fileName)
{
	JNIEnv *env;
    if(JNI_OK != javaVM->AttachCurrentThread(&env, 0))
    {
        __android_log_print(7, "CallJavaCallback", "AttachCurrentThread failed");
        return;
    }

    jmethodID method = env->GetStaticMethodID(activityClass, "OnPlayWav", "(Ljava/lang/String;)V");
    if(method == 0)
    {
        __android_log_print(7, "CallJavaCallback", "GetStaticMethodID failed");
        return;
    }

    jstring jcmd = env->NewStringUTF(fileName);
    env->CallStaticVoidMethod(activityClass, method, jcmd);
}