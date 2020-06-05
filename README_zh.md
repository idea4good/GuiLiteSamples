<p align="center">
    <img src="doc/GuiLiteCube.gif" alt="Image" width="600" height="300"/>
</p>

# 用最少的代码，演绎GUI的精彩
![badge_build](https://img.shields.io/badge/build-passing-brightgreen.svg) ![badge_docker](https://img.shields.io/badge/docker%20build-passing-brightgreen.svg) ![badge_platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS%20%7C%20iOS%20%7C%20Android%20%7C%20MCU-brightgreen.svg) ![badge_lincense](https://img.shields.io/badge/license-Apache%202-blue.svg) ![badge_lincense](https://img.shields.io/badge/architecture-amd64%20%7C%20arm%20%7C%20arm64-blue.svg) 
- GuiLite samples包括19个跨平台项目，他们都是基于[GuiLite](https://github.com/idea4good/GuiLite)编写的小应用，用来说明GuiLite的设计及使用方法，这些小应用可以运行在：iOS，Android，Linux，Windows，Mac，及**有（无）操作系统的MCU**平台上。
- GuiLite samples编译成功率100%，可以运行在市面所有的：PC，手机，单片机及各种嵌入式（IoT）设备上。
- 支持多种IDE开发调试: Visual Studio, Qt Creator, Keil
- GuiLite Samples可以运行在网页上，并形成3D效果，详情请访问[GuiLiteWeb](https://github.com/idea4good/GuiLiteWeb)
- GuiLite samples可运行在**Docker容器**里面，具体命令如下:
  - `sudo docker run -it --privileged -v /dev:/dev-share idea4good/gui-lite:latest bash /run.sh`

## 单片机系列:
<table>
  <tr>
    <td align="center"><a href="HelloStar/UIcode/UIcode.cpp"><img src="doc/HelloStar.gif" width="200px;"/><br /><sub><b>星空效果</b></sub></a>
    <td align="center"><a href="HelloParticle/UIcode/UIcode.cpp"><img src="doc/HelloParticle.gif" width="200px;"/><br /><sub><b>粒子效果</b></sub></a>
    <td align="center"><a href="HelloWave/UIcode/UIcode.cpp"><img src="doc/HelloWave.gif" width="200px;"/><br /><sub><b>波形控件</b></sub></a>
    <td align="center"><a href="HelloNoTouch/UIcode/UIcode.cpp"><img src="doc/HelloNoTouch.gif" width="200px;"/><br /><sub><b>按键导航、点击窗体</b></sub></a>
  </tr>

  <tr>
    <td align="center"><a href="HelloMario/UIcode/UIcode.cpp"><img src="doc/HelloMario.gif" width="200px;"/><br /><sub><b>多图层GUI</b></sub></a>
    <td align="center"><a href="HelloNets/UIcode/UIcode.cpp"><img src="doc/HelloNets-mcu.gif" width="200px;"/><br /><sub><b>3D效果</b></sub></a>
    <td align="center"><a href="Hello3D/UIcode/UIcode.cpp"><img src="doc/Hello3D.gif" width="200px;"/><br /><sub><b>3D效果</b></sub></a>
    <td align="center"><a href="HelloCircle/UIcode/UIcode.cpp"><img src="doc/HelloCircle.gif" width="200px;"/><br /><sub><b>3D效果</b></sub></a>
  </tr>

  <tr>
    <td align="center"><a href="HelloTimer/UIcode/UIcode.cpp"><img src="doc/HelloTimer.gif" width="200px;"/><br /><sub><b>智能时钟</b></sub></a>
    <td align="center"><a href="HelloMolecule/UIcode/UIcode.cpp"><img src="doc/HelloMolecule.gif" width="200px;"/><br /><sub><b>分子运动效果</b></sub></a>
    <td align="center"><a href="Hello3Dwave/UIcode/UIcode.cpp"><img src="doc/Hello3Dwave.gif" width="200px;"/><br /><sub><b>3D波形效果</b></sub></a>
  </tr>
</table>

- 单片机硬件配置：STM32F103ZET6(512K ROM，64K RAM) + 240 * 320 16位TFT屏
- 单片机软件配置：无操作系统 + GuiLite
- [移植方法 -- 适用于任意单片机平台？](HelloWave/README.md#how-to-port-on-any-type-of-mcu)
- 该实例亦可支持Windows和Linux平台

## Hello Transparent
![HelloTransparent](doc/HelloTransparent.gif)

Hello Transparent 仅有[300多行代码](HelloTransparent/UIcode/UIcode.cpp) 用来实现“透明”窗口， 该实例可支持Windows，Linux和Qt平台。

## Hello Scroll
![HelloScroll](doc/HelloScroll.gif)

Hello Scroll 仅有[300多行代码](HelloScroll/UIcode/UIcode.cpp)，实现了“滚动控件”，并演示了应用方法。该实例可支持Windows，Linux和Qt平台。

## Hello Nets
![HelloNets-pc](doc/HelloNets-pc.gif)

Hello Nets 仅有[100多行代码](HelloNets/UIcode/UIcode.cpp)，用于向初学者展示：如何使用GuiLite模拟3D物理过程。该实例可支持Windows，Linux和单片机平台。

## Hello Widgets
![HelloWidgets](doc/HelloWidgets.gif)

Hello Widgets 仅有[100多行代码](HelloWidgets/UIcode/UIcode.cpp)，用于向初学者展示：如何使用GuiLite自带的控件。该实例可支持Windows和Linux平台。

## Hello Animation
![HelloAnimation](doc/HelloAnimation.gif)

Hello Animation 仅有[100多行代码](HelloAnimation/UIcode/UIcode.cpp)，用于向初学者展示：如何制作动画。该实例可支持Windows和Linux平台。

## Hello Slide
![HelloSlide](doc/HelloSlide.gif)

Hello Slide 仅有[100多行代码](HelloSlide/UIcode/UIcode.cpp)，用于向初学者展示：如何制作滑屏界面。该实例可支持Windows和Linux平台。

## Hello Font
![HelloFont](doc/HelloFont.gif)

Hello Font 仅有[100多行代码](HelloFont/UIcode/UIcode.cpp)，用于向初学者展示：如何基于UTF-8，实现多语言。该实例可支持Windows和Linux平台。

## Hello GuiLite
![HelloGuiLite](doc/HelloGuiLite.gif)

Hello GuiLite 仅有[100多行代码](HelloGuiLite/UIcode/helloGL.cpp)，用于向初学者展示：初始化GuiLite，布局UI元素，消息映射。该实例可支持Windows和Linux平台。

## Host Monitor
在iOS，Mac下的运行效果:

![Mac](doc/Mac.gif) ![iOS](doc/Ios.landscape.gif)

在Android，嵌入式ARM Linux下的运行效果:

![Android](doc/Android.gif) ![Linux](doc/Linux.gif)

在Windows混合现实下的运行效果:

![Win MR](doc/WinMR.gif)

HostMonitor有2千行UI代码, 用来布局UI和自定义控件
### 代码走读
- HostMonitor\UIcode\source\ui_layout: **布局UI**
- HostMonitor\UIcode\source\ui_ctrl_ex: **自定义控件**

### 跨平台办法
- HostMonitor\BuildAndroid: **Java 语言, 用于Android平台**
- HostMonitor\BuildIOS: **Swift code, 用于 iOS平台**
- HostMonitor\BuildLinux: **C 语言, 用于Linux平台**
- HostMonitor\BuildWin32: **C 语言, 用于Windows**
- HostMonitor\BuildUWP: **CX 语言, 用于通用Windows平台(包括：虚拟/混合现实)**
- HostMonitor\BuildMacCmd: **Swift语言, 用于Mac命令行模式**
- HostMonitor\BuildMacCocoa: **Swift语言, 用于Mac图形应用**
- HostMonitor\BuildGo: **Go语言 + C++, 用于Linux平台**

[编译"host monitor"](HostMonitor/README.md)

[手机连串口设备](doc/Serial.md)

[下载体验Android版App](http://zhushou.360.cn/detail/index/soft_id/1754231)

## 一些建议
是不是感觉很复杂？我们只是资质平庸的开发者，我们能做到的，你也可以！
- 敢于编译、运行
- 敢于修改代码
- 敢于开创自己的UI

## 代码镜像
[国内码云链接](https://gitee.com/idea4good/GuiLiteSamples)

## 致谢
感谢开发者群的所有同学，是你们塑造了今天的GuiLite！也欢迎新的大神/小白加入我们。
<table>
  <tr>
    <td align="center"><a href="https://jq.qq.com/?_wv=1027&k=qfvGGAa7"><img src="doc/qq.group-1.jpg" width="240px;"/><br /><sub><b>大群：527251257</b></sub></a>
    <td align="center"><a href="https://jq.qq.com/?_wv=1027&k=yKnUJj1B"><img src="doc/qq.group-2.jpg" width="240px;"/><br /><sub><b>中群：841031761</b></sub></a>
    <td align="center"><a href="https://jq.qq.com/?_wv=1027&k=5hc3qwj"><img src="doc/qq.group-3.jpg" width="240px;"/><br /><sub><b>小群：717471210</b></sub></a>
  </tr>
</table>
