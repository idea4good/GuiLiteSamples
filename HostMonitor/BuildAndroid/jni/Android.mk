LOCAL_PATH := $(call my-dir)



include $(CLEAR_VARS)

LOCAL_MODULE    := native

LOCAL_SRC_FILES := native.cpp call_java.cpp

LOCAL_LDLIBS := libnative.a

LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog -ljnigraphics

LOCAL_CPPFLAGS += -fexceptions -lstdc++



include $(BUILD_SHARED_LIBRARY)