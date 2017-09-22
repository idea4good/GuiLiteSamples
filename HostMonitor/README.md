## How to build/run for Windows?
1. build sample.lib:
- Open "SampleCode\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP(universal windows platform, you can run it with "Mixed Reality Portal"):
- Copy "SampleCode\debug\sample.lib" you build to "BuildWindows\sample_uwp_cpp\libs\x86(or x64)"
- Open "BuildWindows\sample.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

## How to build/run for Linux（x64 only）?
1. build sample.lib:
- `cd SampleCode`
- `cmake .`
- `make`

2. build/run Linux APP:
- Copy "SampleCode\source\sample.lib" you build to "BuildLinux\libs"
- `cd BuildLinux`
- `cmake .`
- `make`
- `chmod 777 *`
- `./display | ./sample_native shared-fb`

## How to build/run for Android?
### Install software:
- `sudo apt-get install gcc-arm-linux-androideabi`
- Install Android NDK.

1. build sample.lib:
- `cd SampleCode`
- `cmake cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-androideabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-androideabi-g++" .`
- `make`

2. build Android APP:
- Copy "SampleCode\source\sample.lib" you build to "BuildAndroid\jni\libs"
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
