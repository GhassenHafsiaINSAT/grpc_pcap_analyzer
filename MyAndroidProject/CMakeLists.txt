
cmake_minimum_required(VERSION 3.10)

project(MyAndroidProject C)

set(CMAKE_SYSTEM_VERSION 35)

set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)

set(CMAKE_ANDROID_NDK /opt/android-ndk-r27)

set(CMAKE_SYSTEM_NAME Android)

set(CMAKE_ANDROID_STL_TYPE c++_shared)

set(CMAKE_C_COMPILER /opt/android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android35-clang)

set(CMAKE_CXX_COMPILER /opt/android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android35-clang++)

set(CMAKE_SYSROOT /opt/android-ndk-r27/toolchains/llvm/prebuilt/linux-x86_64/sysroot)

add_executable(test src/test.c)