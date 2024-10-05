export NDK_BUILD=/Users/wm/Library/Android/sdk/ndk/28.0.12433566/ndk-build
# 64-bit
export ARCH=arm64-v8a
# 32-bit
# export ARCH=armeabi

${NDK_BUILD} \
        NDK_PROJECT_PATH=./ \
        APP_BUILD_SCRIPT=./Android.mk \
        NDK_APPLICATION_MK=Application.mk
