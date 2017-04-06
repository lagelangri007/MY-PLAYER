LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_SRC_FILES :=  src/Player.cpp\
	            src/NSurface.cpp\
		    src/PlayerControler.cpp\
                    src/NPlayer.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/../inc\
$(TOP)/frameworks/av/include/media



LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libstlport \
    libgui \
    libui \
    libmedia \
    libstlport \
    libcutils \
    libutils


LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -DPLATFORM_ANDROID
LOCAL_MODULE := NPlayer
include $(BUILD_EXECUTABLE)

