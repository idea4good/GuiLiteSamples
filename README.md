# GuiLite Samples - It's you make UI beautiful, not UI framework!
[中文](doc/README-cn.md)

- GuiLite samples contain 8 cross-platform projects. They all based on [GuiLite](https://github.com/idea4good/GuiLite). They could show you how to use GuiLite's interface, and how GuiLite works on iOS, Android, GNU/Linux, Windows and macOS platform.
- GuiLite samples could pass compiling in 100%, could run on all kinds of PC, phones, MCU and embedded(IoT) devices.
- GuiLite samples could run in **Docker container** with single command below:
  - `sudo docker run -it --privileged -v /dev:/dev-share idea4good/gui-lite:latest bash /run.sh`

## MCU demos: Hello Mario + Hello Particle + Hello Wave + Hello Navigation
![HelloMario](doc/HelloMario.gif)&nbsp;&nbsp;![HelloParticle](doc/HelloParticle.gif)&nbsp;&nbsp;![HelloWave](doc/HelloWave.gif)&nbsp;&nbsp;![HelloNavigation](doc/HelloNavigation.gif)
- MCU Hardware: STM32F103ZET6(512K ROM, 64K RAM) + 240*320 16bits color TFT LCD
- MCU Software: No OS, Only GuiLite
- Hello Mario has [100+ lines code](HelloMario/UIcode/UIcode.cpp), showing you how to develop a multi-layer UI system.
- Hello Particle has [100- lines code](HelloParticle/UIcode/UIcode.cpp), showing you how to develop a particle system.
- Hello Wave has [100+ lines code](HelloWave/UIcode/UIcode.cpp), showing you how to use wave widget.
Hello Navigation has only [100+ lines code](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloNavigation/UIcode/UIcode.cpp), showing you how to navigate/click widgets by hard button.
- [How to porting for any MCU?](HelloWave/README.md#How-to-port-on-any-MCU-)
- Also support: Windows & Linux

## Hello Animation
![HelloAnimation](doc/HelloAnimation.gif)

Hello Animation has only [100+ lines code](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloAnimation/UIcode/UIcode.cpp) for beginner, showing you how to making animation. You can run it on Windows and also Linux.

## Hello Slide
![HelloSlide](doc/HelloSlide.gif)

Hello Slide has only [100+ lines code](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloSlide/UIcode/UIcode.cpp). It shows beginner how to make sliding UI. You can run it on Windows and also Linux.

## Hello Font
![HelloFont](doc/HelloFont.gif)

Hello Font has only [100+ lines code](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloFont/UIcode/UIcode.cpp) .It shows beginner how to use multi-language feature(UTF-8). You can run it on Windows and also Linux.

## Hello GuiLite
![HelloGuiLite](doc/HelloGuiLite.gif)

Hello GuiLite has only [100+ lines code](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloGuiLite/UIcode/helloGL.cpp). It shows beginner how to initialize GuiLite, layout UI widgets, and map messages. You can run it on Windows and also Linux.

## Host Monitor
On Mac & iOS:

![Mac](doc/Mac.gif) ![iOS](doc/Ios.landscape.gif)

On Android & ARM Linux embedded:

![Android](doc/Android.gif) ![Linux](doc/Linux.gif)

On Windows Mixed Reality:

![Win MR](doc/WinMR.gif)

Host Monitor has 2,000 lines of code related to UI, showing you how to make UI layout , and customize/extend your UI widgets.
### Code Description
- HostMonitor\UICode\source\ui_layout: **UI Layout**
- HostMonitor\UICode\source\ui_ctrl_ex: **Customize your widgets**

### Cross platform
- HostMonitor\BuildAndroid: **Java code, for Android**
- HostMonitor\BuildIOS: **Swift code, for iOS**
- HostMonitor\BuildLinux: **C code, for Linux**
- HostMonitor\BuildWin32: **C code, for Windows command mode**
- HostMonitor\BuildUWP: **CX code, for UWP(include Mixed/Virtual Reality)**
- HostMonitor\BuildMacCmd: **Swift code, for Mac command mode**
- HostMonitor\BuildMacCocoa: **Swift code, for Mac APP with UI**
- HostMonitor\BuildGo: **Golang & C++, for Linux**

[Build "host monitor"](HostMonitor/README.md)

[UART on Android phone](doc/Serial.md)

[Download Android APP](http://zhushou.360.cn/detail/index/soft_id/1754231)

## Suggestions
Looks complex? Trust me that you can do everything we did because we are the same.
- Dare to build it
- Dare to make your own modification
- Dare to create your UI framework

## Repository Mirror
[Gitee in China](https://gitee.com/idea4good/GuiLiteSamples)

## Thanks
Thanks the help from QQ group, you guys make GuiLite better! And we welcome you to join us.

![QQ group: 841031761](doc/qq.group.jpg)
