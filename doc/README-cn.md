# GuiLite Samples - 是你造就了漂亮的界面，而不是UI框架
- GuiLite samples包括5个跨平台工程，他们都是基于[GuiLite](https://github.com/idea4good/GuiLite)编写的实际应用，用来说明GuiLite的接口使用方法，并让你的程序同时运行在：iOS，Android，Linux，Windows，Mac平台上。
- GuiLite samples极易编译，在QQ开发群的帮助下，现在的编译通过率接近100%

## Hello Animation
![HelloAnimation](HelloAnimation.gif)

Hello Animation 仅有[100多行代码](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloAnimation/UIcode/UIcode.cpp)，用于向初学者展示：如何制作动画。该实例可支持Windows和Linux平台。

## Hello Slide
![HelloSlide](HelloSlide.gif)

Hello Slide 仅有[100多行代码](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloSlide/UIcode/UIcode.cpp)，用于向初学者展示：如何制作滑屏界面。该实例可支持Windows和Linux平台。

## Hello Font
![HelloFont](HelloFont.gif)

Hello Font 仅有[100多行代码](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloFont/UIcode/UIcode.cpp)，用于向初学者展示：如何基于UTF-8，实现多语言。该实例可支持Windows和Linux平台。

## Hello GuiLite
![HelloGuiLite](HelloGuiLite.gif)

Hello GuiLite 仅有[100多行代码](https://github.com/idea4good/GuiLiteSamples/blob/master/HelloGuiLite/UIcode/helloGL.cpp)，用于向初学者展示：初始化GuiLite，布局UI元素，消息映射。该实例可支持Windows和Linux平台。

## Host Monitor
在iOS，Mac下的运行效果:

![Mac](Mac.gif) ![iOS](Ios.landscape.gif)

在Android，嵌入式ARM Linux下的运行效果:

![Android](Android.gif) ![Linux](Linux.gif)

在Windows混合现实下的运行效果:

![Win MR](WinMR.gif)

HostMonitor有2千行UI代码, 用来布局UI和自定义控件
### 代码走读
- HostMonitor\SampleCode\source\ui_tree: **布局UI**
- HostMonitor\SampleCode\source\ui_ctrl_ex: **自定义控件**

### 跨平台办法
- HostMonitor\BuildAndroid: **Java 语言, 用于Android平台**
- HostMonitor\BuildIOS: **Swift code, 用于 iOS平台**
- HostMonitor\BuildLinux: **C 语言, 用于Linux平台**
- HostMonitor\BuildWin32: **C 语言, 用于Windows控制台**
- HostMonitor\BuildUWP: **CX 语言, 用于通用Windows平台(包括：虚拟/混合现实)**
- HostMonitor\BuildMacCmd: **Swift语言, 用于Mac命令行模式**
- HostMonitor\BuildMacCocoa: **Swift语言, 用于Mac图形应用**

[编译"host monitor"](HostMonitor/README.md)

[手机连串口设备](Serial.md)

[下载体验Android版App](http://zhushou.360.cn/detail/index/soft_id/1754231)

## 一些建议
是不是感觉很复杂？我们只是资质平庸的开发者，我们能做到的，你也可以！
- 敢于编译、运行
- 敢于修改代码
- 敢于开创自己的UI

## 代码镜像
[国内码云链接](https://gitee.com/idea4good/GuiLiteSamples)

## 致谢
感谢开发者群的所有同学，是你们塑造了今天的GuiLite！也欢迎你加入我们。

![QQ group: 527251257](qq.group.jpg)
