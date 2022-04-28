<p align="center">
    <img src="doc/GuiLiteCube.gif" alt="Image" width="600" height="300"/>
</p>

# Build wonderful GUI with a few lines of code
![badge_build](https://img.shields.io/badge/build-passing-brightgreen.svg) ![badge_docker](https://img.shields.io/badge/docker%20build-passing-brightgreen.svg) ![badge_platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS%20%7C%20iOS%20%7C%20Android%20%7C%20MCU-brightgreen.svg) ![badge_lincense](https://img.shields.io/badge/license-Apache%202-blue.svg) ![badge_lincense](https://img.shields.io/badge/architecture-amd64%20%7C%20arm%20%7C%20arm64-blue.svg) 

[中文](README_zh.md)
- GuiLite samples contain 21 cross-platform projects. They all based on [GuiLite](https://github.com/idea4good/GuiLite). They could show you how to use GuiLite's interface, and how GuiLite works on iOS, Android, GNU/Linux, Windows and macOS platform.
- GuiLite samples could pass compiling in 100%, could run on all kinds of PC, phones, MCU and embedded(IoT) devices.
- Suppoort IDE: Visual Studio, Qt Creator, Keil 
- GuiLite Samples could run on web page, and make 3D feature with WebGL, visit [GuiLiteWeb](https://github.com/idea4good/GuiLiteWeb) to get more details
- GuiLite samples could run in **Docker container** with single command below:
  - `sudo docker run -it --privileged -v /dev:/dev-share idea4good/gui-lite:latest bash /run.sh`

## MCU demos:
<table>
  <tr>
    <td align="center"><a href="HelloStar/UIcode/UIcode.cpp"><img src="doc/HelloStar.gif" width="200px;"/><br /><sub><b>star field effect</b></sub></a>
    <td align="center"><a href="HelloParticle/UIcode/UIcode.cpp"><img src="doc/HelloParticle.gif" width="200px;"/><br /><sub><b>particle effect</b></sub></a>
    <td align="center"><a href="HelloWave/UIcode/UIcode.cpp"><img src="doc/HelloWave.gif" width="200px;"/><br /><sub><b>wave widget</b></sub></a>
    <td align="center"><a href="HelloNoTouch/UIcode/UIcode.cpp"><img src="doc/HelloNoTouch.gif" width="200px;"/><br /><sub><b>navigate/click widgets</b></sub></a>
  </tr>

  <tr>
    <td align="center"><a href="HelloMario/UIcode/UIcode.cpp"><img src="doc/HelloMario.gif" width="200px;"/><br /><sub><b>multi-layer GUI</b></sub></a>
    <td align="center"><a href="HelloNets/UIcode/UIcode.cpp"><img src="doc/HelloNets-mcu.gif" width="200px;"/><br /><sub><b>3D effect</b></sub></a>
    <td align="center"><a href="Hello3D/UIcode/UIcode.cpp"><img src="doc/Hello3D.gif" width="200px;"/><br /><sub><b>3D effect</b></sub></a>
    <td align="center"><a href="HelloCircle/UIcode/UIcode.cpp"><img src="doc/HelloCircle.gif" width="200px;"/><br /><sub><b>3D effect</b></sub></a>
  </tr>

  <tr>
    <td align="center"><a href="HelloTimer/UIcode/UIcode.cpp"><img src="doc/HelloTimer.gif" width="200px;"/><br /><sub><b>smart timer</b></sub></a>
    <td align="center"><a href="HelloMolecule/UIcode/UIcode.cpp"><img src="doc/HelloMolecule.gif" width="200px;"/><br /><sub><b>molecule movement effect</b></sub></a>
    <td align="center"><a href="Hello3Dwave/UIcode/UIcode.cpp"><img src="doc/Hello3Dwave.gif" width="200px;"/><br /><sub><b>3D wave effect</b></sub></a>
    <td align="center"><a href="HelloPendulum/UIcode/UIcode.cpp"><img src="doc/HelloPendulum.gif" width="200px;"/><br /><sub><b>HelloPendulum effect</b></sub></a>
  </tr>
</table>

- MCU Hardware: STM32F103ZET6(512K ROM, 64K RAM) + 240 * 320 16bits color TFT LCD
- MCU Software: No OS, Only GuiLite
- [How to porting for any MCU?](HelloWave/README.md#how-to-port-on-any-type-of-mcu)
- Also support: Windows / Linux / Qt

## Hello Transparent
![HelloTransparent](doc/HelloTransparent.gif)

Hello Transparent has only [300+ lines code](HelloTransparent/UIcode/UIcode.cpp) for transparent widgets. You can run it on Windows, Linux and Qt.

## Hello Scroll
![HelloScroll](doc/HelloScroll.gif)

Hello Scroll has only [300+ lines code](HelloScroll/UIcode/UIcode.cpp) for scroll widgets. You can run it on Windows, Linux and Qt.

## Hello Nets
![HelloNets-pc](doc/HelloNets-pc.gif)

Hello Nets has only [100+ lines code](HelloNets/UIcode/UIcode.cpp) for beginner, showing you how to build 3D physics App with GuiLite. You can run it on Windows, Linux and MCU.

## Hello Widgets
![HelloWidgets](doc/HelloWidgets.gif)

Hello Widgets has only [100+ lines code](HelloWidgets/UIcode/UIcode.cpp) for beginner, showing you how to develop GUI with GuiLite widgets. You can run it on Windows and Linux.

## Hello Animation
![HelloAnimation](doc/HelloAnimation.gif)

Hello Animation has only [100+ lines code](HelloAnimation/UIcode/UIcode.cpp) for beginner, showing you how to making animation. You can run it on Windows and Linux.

## Hello Slide
![HelloSlide](doc/HelloSlide.gif)

Hello Slide has only [100+ lines code](HelloSlide/UIcode/UIcode.cpp). It shows beginner how to make sliding UI. You can run it on Windows and Linux.

## Hello Font
![HelloFont](doc/HelloFont.gif)

Hello Font has only [100+ lines code](HelloFont/UIcode/UIcode.cpp) .It shows beginner how to use multi-language feature(UTF-8). You can run it on Windows and Linux.

## Hello GuiLite
![HelloGuiLite](doc/HelloGuiLite.gif)

Hello GuiLite has only [100+ lines code](HelloGuiLite/UIcode/helloGL.cpp). It shows beginner how to initialize GuiLite, layout UI widgets, and map messages. You can run it on Windows and Linux.

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
- HostMonitor\BuildWin32: **C code, for Windows**
- HostMonitor\BuildUWP: **CX code, for UWP(include Mixed/Virtual Reality)**
- HostMonitor\BuildMacCmd: **Swift code, for Mac command mode**
- HostMonitor\BuildMacCocoa: **Swift code, for Mac APP with UI**
- HostMonitor\BuildGo: **Golang + C++, for Linux**

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
Thanks the help from QQ group, you guys make GuiLite better! And welcome to join us.
<table>
  <tr>
    <td align="center"><a href="https://jq.qq.com/?_wv=1027&k=O714kulz"><img src="doc/qq.group-5.png" width="240px;"/><br /><sub><b>開發群🔑：616696441</b></sub></a>
  </tr>
</table>
欢迎有条件的同学加入“超级群”🚄⏪⏪⏪，一同打造全球最强Lite GUI👑
