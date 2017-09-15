 # GuiLite Sample
Welcome GuiLite Sample repo!

## How to build/run for Windows?
1. build sample.lib:
- Open "sample\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP(universal windows platform, you can run it with "Mixed Reality Portal"):
- Copy "sample\debug\sample.lib" you build to "BuildWindows\sample_uwp_cpp\libs\x86(or x64)"
- Open "BuildWindows\sample.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

## How to build/run for Linux?
1. build sample.lib:
- `cd sample`
- `cmake .`
- `make`

2. build/run Linux APP:
- Copy "sample\source\sample.lib" you build to "BuildLinux\libs"
- `cd BuildLinux`
- `cmake .`
- `make`
- `chmod 777 *`
- `./display-x86 | ./sample_native shared-fb` for Linux 32 bits.
- `./display-x64 | ./sample_native shared-fb` for Linux 64 bits.

## How to build/run for Android?
### Install software:
- `sudo apt-get install gcc-arm-linux-androideabi`
- Install Android NDK.

1. build sample.lib:
- `cd sample`
- `cmake cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-androideabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-androideabi-g++" .`
- `make`

2. build Android APP:
- Copy "sample\source\sample.lib" you build to "BuildAndroid\jni\libs"
- `cd BuildAndroid\jni\libs`
- `./merge_libs.sh`
- `cd BuildAndroid\jni`
- `ndk-build clean`
- `ndk-build`
- Copy "BuildAndroid\libs\armeabi-v7a\libnative.so" you build to "BuildAndroid\app\libs\armeabi-v7a"
- Open "BuildAndroid" with Android studio
- Click `build/debug/run`

Note:
Run `./merge_libs.sh` meet error, maybe you need run `dos2unix merge_libs.sh`
