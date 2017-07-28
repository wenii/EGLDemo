# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

THIRD_PARTY := ../../thirdparty

include $(CLEAR_VARS)

LOCAL_MODULE    := EGLPlatform

LOCAL_C_INCLUDES := ../thirdparty

LOCAL_SRC_FILES := App.cpp  \
                   Egl.cpp \
                   Shader.cpp \
                   MessageQueue.cpp \
                   DynamicArray.cpp \
                   PackageFiles.cpp \
                   Texture.cpp \
                   JniUtils.cpp \
                   AppInterface.cpp \
                   Camera.cpp


LOCAL_SRC_FILES +=	$(THIRD_PARTY)/stb/stb_image.c \
					$(THIRD_PARTY)/stb/stb_image_write.c

LOCAL_SRC_FILES +=	$(THIRD_PARTY)/minizip/ioapi.c \
					$(THIRD_PARTY)/minizip/miniunz.c \
					$(THIRD_PARTY)/minizip/mztools.c \
					$(THIRD_PARTY)/minizip/unzip.c \
					$(THIRD_PARTY)/minizip/zip.c


include $(BUILD_STATIC_LIBRARY)
