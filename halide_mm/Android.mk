LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := halide_mm
LOCAL_SRC_FILES := $(LOCAL_PATH)/aot_ndk_arm/halide_mm.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_CPPFLAGS := -I$(LOCAL_PATH)/aot_ndk_arm
LOCAL_CPPFLAGS += -I $(LOCAL_PATH)/build_inc

LOCAL_MODULE := mm_arm
LOCAL_LDLIBS += -L$(LOCAL_PATH)/aot_ndk_arm -llog

LOCAL_SRC_FILES := mm.cpp
LOCAL_STATIC_LIBRARIES := halide_mm

include $(BUILD_EXECUTABLE)


LOCAL_MODULE := halide_mm_int
LOCAL_SRC_FILES := $(LOCAL_PATH)/aot_ndk_arm_int/halide_mm.a
include $(PREBUILT_STATIC_LIBRARY)

LOCAL_CPPFLAGS := -I$(LOCAL_PATH)/aot_ndk_arm_int
LOCAL_CPPFLAGS += -I $(LOCAL_PATH)/build_inc

LOCAL_MODULE := mm_arm_int
LOCAL_LDLIBS += -L$(LOCAL_PATH)/aot_ndk_arm_int -llog

LOCAL_SRC_FILES := mm_int.cpp
LOCAL_STATIC_LIBRARIES := halide_mm_int

include $(BUILD_EXECUTABLE)

