<p align="center">
    <img src="doc/GuiLiteCube.gif" alt="Image" width="600" height="300"/>
</p>

# Build wonderful GUI with a few lines of code
![badge_build](https://img.shields.io/badge/build-passing-brightgreen.svg) ![badge_docker](https://img.shields.io/badge/docker%20build-passing-brightgreen.svg) ![badge_platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS%20%7C%20iOS%20%7C%20Android%20%7C%20MCU-brightgreen.svg) ![badge_lincense](https://img.shields.io/badge/license-Apache%202-blue.svg) ![badge_lincense](https://img.shields.io/badge/architecture-amd64%20%7C%20arm%20%7C%20arm64-blue.svg) 

[中文](README_zh.md)
- GuiLite samples contain 21 cross-platform projects that are all based on [GuiLite](https://github.com/idea4good/GuiLite). They can show you how to use GuiLite's interface and how GuiLite works on iOS, Android, GNU/Linux, Windows, and macOS platforms.
- GuiLite samples have been tested to compile successfully 100% of the time and run on all kinds of devices, including PCs, phones, microcontrollers, and embedded Internet of Things (IoT) devices.
- Supported IDEs: Visual Studio, Qt Creator, Keil
- GuiLite samples can run on web pages and make 3D features with WebGL. For more details, visit [GuiLiteWeb](https://github.com/idea4good/GuiLiteWeb).
- GuiLite samples can run in a **Docker container** with the single command below:
  - `sudo docker run -it --privileged -v /dev:/dev-share idea4good/gui-lite:latest bash /run.sh`

## Microcontroller  demos:
<table>
  <tr>
    <td align="center"><a href="HelloStar/UIcode/UIcode.cpp"><img src="doc/HelloStar.gif" width="200px;"/><br /><sub><b>star field effect</b></sub></a>
    <td align="center"><a href="HelloParticle/UIcode/UIcode.cpp"><img src="doc/HelloParticle.gif" width="200px;"/><br /><sub><b>particle effect</b></sub></a>
    <td align="center"><a href="HelloWave/UIcode/UIcode.cpp"><img src="doc/HelloWave.gif" width="200px;"/><br /><sub><b>wave widget</b></sub></a>
    <td align="center"><a href="HelloKeypad/UIcode/UIcode.cpp"><img src="doc/HelloKeypad.gif" width="200px;"/><br /><sub><b>navigate/click widgets</b></sub></a>
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

- MCU Hardware: STM32F103ZET6(512K ROM, 64K RAM) with 240 * 320 16bits color TFT LCD
- MCU Software: No operating system (OS) with GuiLite embedded GUI framework
- [How to port on any type of microcontroller (MCU)?](doc/how-to-port-on-mcu.md)
- Also supports: Windows / Linux / Qt

## Hello Transparent
![HelloTransparent](doc/HelloTransparent.gif)

Hello Transparent is a [300+ lines code](HelloTransparent/UIcode/UIcode.cpp) sample for transparent widgets. It runs on Windows, Linux, and Qt.

## Hello Scroll
![HelloScroll](doc/HelloScroll.gif)

Hello Scroll is a [300+ lines code](HelloScroll/UIcode/UIcode.cpp) sample for scroll widgets. It runs on Windows, Linux, and Qt.

## Hello Nets
![HelloNets-pc](doc/HelloNets-pc.gif)

Hello Nets is a [100+ lines code](HelloNets/UIcode/UIcode.cpp) sample to build 3D physics apps with GuiLite. It runs on Windows, Linux, and MCUs.

## Hello Widgets
![HelloWidgets](doc/HelloWidgets.gif)

Hello Widgets is a [100+ lines code](HelloWidgets/UIcode/UIcode.cpp) sample to develop GUI with GuiLite widgets. It runs on Windows, Linux, and MCUs.

## Hello Animation
![HelloAnimation](doc/HelloAnimation.gif)

Hello Animation is a [100+ lines code](HelloAnimation/UIcode/UIcode.cpp) sample to create animation. It runs on Windows, Linux, and MCUs.

## Hello Slide
![HelloSlide](doc/HelloSlide.gif)

Hello Slide is a [100+ lines code](HelloSlide/UIcode/UIcode.cpp) sample for making sliding UI. It runs on Windows, Linux, and MCUs.

## Hello Font
![HelloFont](doc/HelloFont.gif)

Hello Font is a [100+ lines code](HelloFont/UIcode/UIcode.cpp) sample for using multi-language feature(UTF-8). It runs on Windows, Linux, and MCUs.

## Hello GuiLite
![HelloGuiLite](doc/HelloGuiLite.gif)

Hello GuiLite is a [100+ lines code](HelloGuiLite/UIcode/helloGL.cpp) sample to initialize GuiLite, layout UI widgets, and map messages. It runs on Windows, Linux, and MCUs.

## Host Monitor
On Mac & iOS:

![Mac](doc/Mac.gif) ![iOS](doc/Ios.landscape.gif)

On Android & ARM Linux embedded:

![Android](doc/Android.gif) ![Linux](doc/Linux.gif)

On Windows Mixed Reality:

![Win MR](doc/WinMR.gif)

Host Monitor has 2,000 lines of UI code, showing how to create layouts and customize widgets.

### Code Description
- HostMonitor\UICode\source\ui_layout: **UI Layout**
- HostMonitor\UICode\source\ui_ctrl_ex: **Customize your widgets**

### Cross platform
- HostMonitor\BuildAndroid: **Android (Java)**
- HostMonitor\BuildIOS: **iOS (Swift)**
- HostMonitor\BuildLinux: **for Linux (C)**
- HostMonitor\BuildWin32: **Windows (C)**
- HostMonitor\BuildUWP: **UWP including Mixed/Virtual Reality (CX)**
- HostMonitor\BuildMacCmd: **Mac command line (Swift)**
- HostMonitor\BuildMacCocoa: **MAC UI (Swift)**
- HostMonitor\BuildGo: **Linux (Golang + C++)**

[Build "host monitor"](HostMonitor/README.md)

[UART on Android phone](doc/Serial.md)

[Download Android APP](http://zhushou.360.cn/detail/index/soft_id/1754231)

## Suggestions
Looks complex? Trust me, you can do it. We started where you are now, and we built amazing things.
- Dare to build it
- Dare to make your own modifications.
- Dare to create your own UI framework.

## Repository Mirror
[Gitee in China](https://gitee.com/idea4good/GuiLiteSamples)

## Thanks
Thank you to everyone in the QQ group for your help in making GuiLite better! join us and help us make GuiLite even better!

<table>
  <tr>
    <td align="center"><a href="https://jq.qq.com/?_wv=1027&k=O714kulz"><img src="doc/qq.group-5.png" width="240px;"/><br /><sub><b>開發群🔑：616696441</b></sub></a>
    <td align="center"><img src="doc/VXGZH.jpg" width="240px;"/><br /><sub><b>公众号🔑：阿布编程</b></sub>
  </tr>
</table>
欢迎有条件的同学加入“超级群”🚄⏪⏪⏪，一同打造全球最强Lite GUI👑
