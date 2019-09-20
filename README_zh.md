<p align="center">
    <img src="doc/GuiLiteCube.gif" alt="Image" width="600" height="300"/>
</p>

# GuiLite Samples - 小Demo，说清GUI原理
![badge_build](https://img.shields.io/badge/build-passing-brightgreen.svg) ![badge_docker](https://img.shields.io/badge/docker%20build-passing-brightgreen.svg) ![badge_platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS%20%7C%20iOS%20%7C%20Android%20%7C%20MCU-brightgreen.svg) ![badge_lincense](https://img.shields.io/badge/license-Apache%202-blue.svg) ![badge_lincense](https://img.shields.io/badge/architecture-amd64%20%7C%20arm%20%7C%20arm64-blue.svg) 
- GuiLite samples包括13个跨平台项目，他们都是基于[GuiLite](https://github.com/idea4good/GuiLite)编写的小应用，用来说明GuiLite的设计及使用方法，这些小应用可以运行在：iOS，Android，Linux，Windows，Mac，及**有（无）操作系统的MCU**平台上。
- GuiLite samples编译成功率100%，可以运行在市面所有的：PC，手机，单片机及各种嵌入式（IoT）设备上。
- 支持多种IDE开发调试: Visual Studio, Qt Creator, Keil
- GuiLite Samples可以运行在网页上，并形成3D效果，详情请访问[GuiLiteWeb](https://github.com/idea4good/GuiLiteWeb)
- GuiLite samples可运行在**Docker容器**里面，具体命令如下:
  - `sudo docker run -it --privileged -v /dev:/dev-share idea4good/gui-lite:latest bash /run.sh`

## 单片机系列: Hello Star + Hello Particle + Hello Wave + Hello NoTouch + Hello Mario + Hello 3D
![HelloStar](doc/HelloStar.gif)&nbsp;&nbsp;![HelloParticle](doc/HelloParticle.gif)&nbsp;&nbsp;![HelloWave](doc/HelloWave.gif)&nbsp;&nbsp;![HelloNoTouch](doc/HelloNoTouch.gif)&nbsp;&nbsp;![HelloMario](doc/HelloMario.gif)&nbsp;&nbsp;![HelloNets-mcu](doc/HelloNets-mcu.gif)
- 单片机硬件配置：STM32F103ZET6(512K ROM，64K RAM) + 240*320 16位TFT屏
- 单片机软件配置：无操作系统 + GuiLite
- Hello Star 仅有[100+行代码](HelloStar/UIcode/UIcode.cpp)，用于向开发者展示：如何使用GuiLite进行“星空”效果的开发。
- Hello Particle 仅有[100-行代码](HelloParticle/UIcode/UIcode.cpp)，用于向开发者展示：如何使用GuiLite进行粒子效果的开发。
- Hello Wave 仅有[100+行代码](HelloWave/UIcode/UIcode.cpp)，用于向开发者展示：如何使用GuiLite进行波形开发。
- Hello NoTouch 仅有[100+行代码](HelloNoTouch/UIcode/UIcode.cpp)，用于向开发者展示：如何在非触摸屏场景下，使用硬按键进行：“移动焦点”和“点击”操作。
- Hello Mario 仅有[100+行代码](HelloMario/UIcode/UIcode.cpp)，重现了“超级玛丽”的游戏片段，用于向开发者展示：如何使用GuiLite进行多图层的开发。
- Hello Nets 仅有[100多行代码](HelloNets/UIcode/UIcode.cpp)，用于向开发者展示：如何使用GuiLite制作3D效果。
- Hello 3D 仅有[100多行代码](Hello3D/UIcode/UIcode.cpp)，它是基于GuiLite制作的最小3D引擎。
- [移植方法 -- 适用于任意单片机平台？](HelloWave/README.md#how-to-port-on-any-type-of-mcu)
- 该实例亦可支持Windows和Linux平台

## Hello 3D
![Hello3D](doc/Hello3D.gif)

Hello 3D是一个超轻量（单片机级别）3D引擎。
- 可以运行资源十分有限的硬件上
- 可以快速建立3D模型，并流畅的运行在各种平台上（例如：Windows, Linux, MCU, Qt）
- 少许3D效果，可以有效提升UI体验

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
感谢开发者群的所有同学，是你们塑造了今天的GuiLite！也欢迎新的大神/小白加入我们。<br>[<img src="doc/qq.group.jpg">](https://jq.qq.com/?_wv=1027&k=5EO8D9i)
