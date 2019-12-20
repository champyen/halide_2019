LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := mm
LOCAL_SRC_FILES := mm.c
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := mm_int
LOCAL_SRC_FILES := mm_int.c
include $(BUILD_EXECUTABLE)

