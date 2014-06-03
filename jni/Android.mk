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

# ------------------------------------------
# Define prebuilt shared libtorrent library
include $(CLEAR_VARS)
LOCAL_MODULE    := libtorrent-rasterbar
LOCAL_SRC_FILES := libs/libtorrent-rasterbar.so
include $(PREBUILT_SHARED_LIBRARY)

# ------------------------------------------
# Build the hello libtorrent library
include $(CLEAR_VARS)
LOCAL_MODULE     := hello

LOCAL_CFLAGS     := -DBOOST_ASIO_HASH_MAP_BUCKETS=1021 \
                    -DBOOST_FILESYSTEM_VERSION=3 \
                    -DUNICODE \
                    -DWITH_SHIPPED_GEOIP_H \
                    -DTORRENT_BUILDING_STATIC \
                    -DBOOST_ASIO_SEPARATE_COMPILATION \
                    -DBOOST_ASIO_ENABLE_CANCELIO \
                    -DTORRENT_USE_ICONV=0 \
                    -DTORRENT_USE_TOMMATH

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SRC_FILES  := hello.cpp

LOCAL_SHARED_LIBRARIES := libtorrent-rasterbar

include $(BUILD_SHARED_LIBRARY)


