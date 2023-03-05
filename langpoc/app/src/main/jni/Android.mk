LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libmstring
LOCAL_CFLAGS := -std=c17 -Wall -Werror
LOCAL_SRC_FILES := \
  mstring.c
LOCAL_LDLIBS := -ldl -llog
include $(BUILD_SHARED_LIBRARY)
