#include <jni.h>
#include <android/log.h>
#include <errno.h>

extern int startHostMonitor(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern int sendTouch2HostMonitor(void* buf, int len, int display_id);
extern void* getUiOfHostMonitor(int display_id, int* width, int* height, bool force_update);
extern void on_receive_data(void* data, int length);

extern void InitJavaEnv(JNIEnv* env, jobject obj);
extern void OnAndroidPlayWav(const char* fileName);

typedef void(*ANDROID_PLAY_WAV)(const char* fileName);
extern ANDROID_PLAY_WAV gAndroidPlayWav;

typedef struct
{
	unsigned int dwMsgId;
	unsigned int dwParam1;
	unsigned int dwParam2;
}OUTMSGINFO;

extern "C" JNIEXPORT jint JNICALL  Java_gui_1lite_1sample_ThreadNative_start_1native(JNIEnv * ev, jobject obj, jint main_cnt, jint sub_cnt)
{
	InitJavaEnv(ev, obj);
	gAndroidPlayWav = OnAndroidPlayWav;
	return startHostMonitor(main_cnt, 1024, 768, sub_cnt, 1024, 370, 2);
}

extern "C" JNIEXPORT jint JNICALL Java_gui_1lite_1sample_ThreadNative_WriteHidFifo( JNIEnv* env, jobject thiz, jint type, jint x, jint y, jint display_id)
{
	OUTMSGINFO msg;
	msg.dwMsgId = type;
	msg.dwParam1 = x;
	msg.dwParam2 = y;
	return sendTouch2HostMonitor(&msg, sizeof(msg), display_id);
}

extern "C" JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_GetBitmapWidth(JNIEnv * env, jobject obj, jint display_id)
{
	int width, height;
	width = height = -1;
	getUiOfHostMonitor(display_id, &width, &height, false);
	return width;
}

extern "C" JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_GetBitmapHeight(JNIEnv * env, jobject obj, jint display_id)
{
	int width, height;
	width = height = -1;
	getUiOfHostMonitor(display_id, &width, &height, false);	
	return height;
}

#include <android/bitmap.h>
#include <string.h>
extern "C" JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_UpdateBitmap(JNIEnv * env, jobject obj, jobject bitmap, jint display_id, jint width, jint height)
{
	AndroidBitmapInfo  	infocolor;
	void*              	pixelscolor;

	if (AndroidBitmap_getInfo(env, bitmap, &infocolor) < 0) {
		return -1;
	}
	if (AndroidBitmap_lockPixels(env, bitmap, &pixelscolor) < 0) {
		return -2;
	}
	void* src = getUiOfHostMonitor(display_id, NULL, NULL, false);
	if(src)
	{
		memcpy(pixelscolor, src, width * height * 2);
	}
	AndroidBitmap_unlockPixels(env, bitmap);
	return 0;
}

extern "C" JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_OnReceiveData(JNIEnv * env, jobject obj, jbyteArray data, jint length)
{
	jbyte* bytedata =env->GetByteArrayElements(data, 0);
	on_receive_data(bytedata, length);
	//env->ReleaseByteArrayElements(data, bytedata, JNI_ABORT);
	return 0;
}
