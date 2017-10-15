## How to build/run for Win32?
1. build sample.lib:
- Open "SampleCode\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP:
- Copy "SampleCode\debug\sample.lib" you build to "BuildWin32\sample_uwp_cpp\libs\x86(or x64)"
- Open "BuildWin32\GuiLite.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`
- Command `ss` you will get snapshot in BuildWin32\sample_native\snapshotx.bmp
- Command `sslp` and open "BuildWin32\sample_native\Display.html" with internet browser(such like: IE, chrome)

## How to build/run for Windows UWP?
depdency: Windows 10(RS2), visul stdio 2015/2017

1. build sample.lib:
- Open "SampleCode\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP(you can run it with "Mixed Reality Portal"):
- Copy "SampleCode\debug\sample.lib" you build to "BuildUWP\sample_uwp_cpp\libs\x86(or x64)"
- Open "BuildUWP\GuiLite.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

## How to build/run for Linux（x64 & arm）?
1. build sample.lib:
- `cd SampleCode`
- `cmake .`
- `make`

2. build/run Linux APP:
- Copy "SampleCode\source\sample.lib" you build to "BuildLinux\libs"
- If ARM: Copy "BuildLinux\libs\arm\libcore.a libgui.a" to overwrite "BuildLinux\libs\libcore.a libgui.a"
- `cd BuildLinux`
- `cmake .`
- `make`
- `chmod 777 *`
- `./display | ./sample_native shared-fb`  -- display is QT APP for display, you should install QT libs.
or:
- `./sample_native 1 8`
- Command `ss` you will get snapshot in BuildLinux\sample_native\snapshotx.bmp
- Command `sslp` and open "BuildLinux\Display.html" with internet browser(such like: Firefox, chrome)

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
