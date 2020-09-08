#include <jni.h>
#include <android/log.h>
#include <errno.h>
#include <cstdlib>

extern void startHostMonitor(void* phy_fb, int screen_width, int screen_height, int color_bytes);
extern void sendTouch2HostMonitor(int x, int y, bool is_down);
extern void* getUiOfHostMonitor(int* width, int* height, bool force_update);
extern void on_receive_data(void* data, int length);

extern void InitJavaEnv(JNIEnv* env, jobject obj);
extern void OnAndroidPlayWav(const char* fileName);

typedef void(*ANDROID_PLAY_WAV)(const char* fileName);
extern ANDROID_PLAY_WAV gAndroidPlayWav;

extern "C" JNIEXPORT jint JNICALL  Java_com_guilite_hostmonitor_ThreadNative_startNative(JNIEnv * ev, jclass obj, jint width, jint height, jint color_bytes)
{
    InitJavaEnv(ev, obj);
    //gAndroidPlayWav = OnAndroidPlayWav;
    startHostMonitor(malloc(width * height * color_bytes), width, height, color_bytes);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_guilite_hostmonitor_ThreadNative_sendTouch( JNIEnv* env, jclass obj, jboolean is_down, jint x, jint y)
{
    sendTouch2HostMonitor(x, y, is_down);
    return 0;
}

#include <android/bitmap.h>
#include <string.h>
extern "C" JNIEXPORT jint JNICALL Java_com_guilite_hostmonitor_ThreadNative_updateBitmap(JNIEnv * env, jclass obj, jobject bitmap, jint width, jint height)
{
    AndroidBitmapInfo  	infocolor;
    void*              	pixelscolor;

    if (AndroidBitmap_getInfo(env, bitmap, &infocolor) < 0) {
        return -1;
    }
    if (AndroidBitmap_lockPixels(env, bitmap, &pixelscolor) < 0) {
        return -2;
    }
    void* src = getUiOfHostMonitor(NULL, NULL, false);
    if(src)
    {
        memcpy(pixelscolor, src, width * height * 2);
    }
    AndroidBitmap_unlockPixels(env, bitmap);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_guilite_hostmonitor_ThreadNative_onReceiveData(JNIEnv * env, jclass obj, jbyteArray data, jint length)
{
    jbyte* bytedata =env->GetByteArrayElements(data, 0);
    on_receive_data(bytedata, length);
    //env->ReleaseByteArrayElements(data, bytedata, JNI_ABORT);
    return 0;
}
