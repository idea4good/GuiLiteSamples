#include <jni.h>
#include <android/log.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" { 

extern "C" int run_native(int main_cnt, int main_width, int main_height, int sub_cnt, int sub_width, int sub_height, int color_bytes);
extern int send_hid_msg(void* buf, int len, unsigned int display_id);
extern void* get_frame_buffer(unsigned int display_id, int* width, int* height);

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

JNIEXPORT jint JNICALL Java_gui_1lite_1sample_ThreadNative_start_1native(JNIEnv * ev, jobject obj, jint main_cnt, jint sub_cnt)
{
	InitJavaEnv(ev, obj);
	gAndroidPlayWav = OnAndroidPlayWav;
	return run_native(main_cnt, 1024, 768, sub_cnt, 1024, 370, 2);
}

JNIEXPORT jint JNICALL Java_gui_1lite_1sample_ThreadNative_WriteHidFifo( JNIEnv* env, jobject thiz, jint type, jint x, jint y, jint display_id)
{
	OUTMSGINFO msg;
	msg.dwMsgId = type;
	msg.dwParam1 = x;
	msg.dwParam2 = y;
	return send_hid_msg(&msg, sizeof(msg), display_id);
}

JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_GetBitmapWidth(JNIEnv * env, jobject obj, jint display_id)
{
	int width, height;
	width = height = -1;
	get_frame_buffer(display_id, &width, &height);
	return width;
}

JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_GetBitmapHeight(JNIEnv * env, jobject obj, jint display_id)
{
	int width, height;
	width = height = -1;
	get_frame_buffer(display_id, &width, &height);	
	return height;
}

#include <android/bitmap.h>
#include <string.h>
JNIEXPORT jint  JNICALL Java_gui_1lite_1sample_ThreadNative_UpdateBitmap(JNIEnv * env, jobject obj, jobject bitmap, jint display_id, jint width, jint height)
{
	AndroidBitmapInfo  	infocolor;
	void*              	pixelscolor;

	if (AndroidBitmap_getInfo(env, bitmap, &infocolor) < 0) {
		return -1;
	}
	if (AndroidBitmap_lockPixels(env, bitmap, &pixelscolor) < 0) {
		return -2;
	}
	void* src = get_frame_buffer(display_id, NULL, NULL);
	if(src)
	{
		memcpy(pixelscolor, src, width * height * 2);
	}
	AndroidBitmap_unlockPixels(env, bitmap);
	return 0;
}

}
#endif

///////////////// Implement functions for libs //////////////////////
void do_assert(const char* file, int line)
{
    __android_log_print(7, "ASSERT", "file: %s, line: %d, error code: 0x%x\n", file, line, errno);
}

void log_out(const char* log)
{
    __android_log_print(7, "LOG", "%s", log);
}
