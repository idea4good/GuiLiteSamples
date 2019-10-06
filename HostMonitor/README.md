# How to build for WinForms - C#?
## GuiLite.lib should be in BuildWinforms\HostMonitorDll, rebuild them if meet link error.
- Open "HostMonitor\BuildWinforms\BuildWinforms.sln" by Visual studio 2017
- Build `sample`, `HostMonitor`, `BuildWinforms` in turn, then run BuildWinforms.

# How to build for Win MFC?
## GuiLite.lib should be in BuildMFC\BuildMFC\libs\x86(x64), rebuild them if meet link error.
- Open "HostMonitor\BuildMFC\HostMonitor.sln" by Visual studio 2017
- Click `F5` to build/run `HostMonitor`

# How to build for Win32?
## GuiLite.lib should be in BuildWin32\libs, rebuild them if meet link error.
- Open "HostMonitor\BuildWin32\HostMonitor.sln" by Visual studio 2017
- Click `F5` to build/run `HostMonitor`, you will see UI in internet browser.

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HostMonitor`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window:
        1. `sudo su`
        2. `sudo ./xWindow 1024 768 | ./HostMonitor shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HostMonitor`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" -D TARGET_ARCH="ARM" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HostMonitor to target Linux device
    - `chmod 777 HostMonitor`
    - `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer

## Q&A:
1. Could not display UI on Ubuntu with framebuffer
    - Enter pure command line mode(Ctrl + Alt + F1), and run again
    - Update Ubuntu to 18.10, and run again
2. Linking error: rebuild libGuiLite.a, and replace them in BuildLinux/libs

# How to build with GoLang?
1. Build UIcode:
- `cd HostMonitor/UIcode`
- If x64/raspberry pi:
    - `cmake .`
    - `make`
    - `cp libUIcode.a ../BuildGo/libs/amd64/`
- If ARM32:
    - `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" .`
    - `make`
    - `cp libUIcode.a ../BuildGo/libs/arm/`
2. Build Golang:
- `cd HostMonitor/BuildGo`
- `go build -o HostMonitor`
3. Run with framebuffer:
- `sudo ./HostMonitor /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
4. Run inside QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- `sudo ./xWindow 1024 768 | ./HostMonitor shared-fb`

# How to build for iOS?
### libGuiLite.a libUIcode.a should be in \BuildIos\BuildIos\libs, rebuild them if meet link error.
- `cd HostMonitor\BuildIos`
- Open `BuildIos.xcodeproj` with Xcode
- Build & Run

# How to build for Mac?
### libGuiLite.a should be in BuildMacCmd\libs, rebuild them if meet link error.
- `cd HostMonitor`
- `cmake -D TARGET_OS="MAC" .`
- `make`

## Run in command mode
- `cd BuildMacCmd`
- `./HostMonitor 1 8`, you will see UI in internet browser(Safari).

## Run in UI mode
### libGuiLite.a libUIcode.a should be in BuildMacCocoa\GuiLiteDemo\libs, rebuild them if meet link error.
- Open `BuildMacCocoa\GuiLiteDemo.xcodeproj` with Xcode
- Build and Run

# How to build/run for Android?
## Install software:
- `sudo apt-get install gcc-arm-linux-androideabi`
- Install Android NDK.

- `cd HostMonitor`
- `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-androideabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-androideabi-g++" .`
- `make`⚠️You will meet: `fatal error: sys/shm.h: No such file` -- Don't worry, ignore it.
- `cp UIcode/libUIcode.a  BuildAndroid/jni/libs`
- `cd BuildAndroid/jni/libs`
- `./merge-libs.sh`
- `cd BuildAndroid\jni`
- `ndk-build clean`
- `ndk-build`
- `copy ..\libs\armeabi-v7a\libnative.so ..\app\libs\armeabi-v7a\`
- Open "BuildAndroid" with Android studio
- Click `build/debug/run`

Note:
Run `./merge_libs.sh` meet error, maybe you need run `dos2unix merge_libs.sh`

# How to build for Windows UWP?
depdency: Windows 10, visul stdio 2015/2017

- Open "UIcode\sample.sln" by Visual studio 2017
- Click `build` 
- `copy UIcode\debug\sample.lib BuildUWP\sample_uwp_cpp\libs\x86(x64)\`
- Open "BuildUWP\HostMonitor.sln" by Visual studio 2017
- Click `build`
- Click `debug/run`

# How to run on VR/MR?
- If VR: run `Mixed Reality Portal`on PC side.
- Take VR/MR device on head, or run simulator.
- press `start`, find the UWP you build and run.

Note: Windows RS3(Build 16299) will be necessary.