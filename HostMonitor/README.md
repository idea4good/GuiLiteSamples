## How to build/run for Windows UWP?
depdency: Windows 10, visul stdio 2015/2017

1. build sample.lib:
- Open "SampleCode\sample.sln" by Visual studio 2017
- Click `build` 

2. build/run Windows APP
- Copy "SampleCode\debug\sample.lib" you build to "BuildUWP\sample_uwp_cpp\libs\x86(or x64)"
- Open "BuildUWP\GuiLite.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

## How to run on VR/MR?
- If VR: run `Mixed Reality Portal`on PC side.
- Take VR/MR device on head, or run simulator.
- press `start`, find the UWP you build and run.

Note: Windows RS3(fall creators update) is needed.

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

## How to build/run for Linux（x64 & arm）?
1. build libsample.a:
- `cd SampleCode`
- `cmake .`
- `make`

2. build Linux APP:
- Copy "SampleCode\source\libsample.a" you build to "BuildLinux\libs"
- If ARM: Copy "BuildLinux\libs\arm\libcore.a libgui.a" to overwrite "BuildLinux\libs\libcore.a libgui.a"
- `cd BuildLinux`
- `cmake .`
- `make`

3. Run with QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- `chmod 777 *`
- If x64:`./display-x64 | ./sample_native shared-fb`
- If ARM:`./display-arm | ./sample_native shared-fb`

4. Run with internet explore:
- `./sample_native 1 8`
- Command `ss` you will get snapshot in BuildLinux\sample_native\snapshotx.bmp
- Command `sslp` and open "BuildLinux\Display.html" with internet browser(such like: Firefox, chrome)

## How to build/run for Android?
### Install software:
- `sudo apt-get install gcc-arm-linux-androideabi`
- Install Android NDK.

1. build sample.lib:
- `cd SampleCode`
- `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-androideabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-androideabi-g++" .`
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

## How to build project using xmake?

Please download and install xmake to build project, you can see [Installation Manual](http://xmake.io/#/home?id=installation)。

#### linux/macosx/windows

```console
$ xmake
```

#### iPhoneos

```console
$ xmake f -p iphoneos
$ xmake
```

#### Android

```console
$ xmake f -p android --ndk=/home/xxx/android-ndk-r10e --sdk=/home/xxx/android-sdk
$ xmake
```

#### Mingw

```console
$ xmake f -p mingw
$ xmake
```

#### Cross compilation

```console
$ xmake f -p cross --sdk=/usr/local/arm-xxx-gcc/ [--toolchains=/sdk/bin] [--cross=arm-linux-]
$ xmake
```

#### Generate IDE Project Files

```console
$ xmake project -k vs2008
$ xmake project -k vs2017 -m "debug,release"
$ xmake project -k makefile
```

If you want to known more info about xmake, please see [xmake documents](http://xmake.io/#/home).
