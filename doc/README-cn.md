# GuiLite Samples - 你自己的精彩
在iOS，Mac下的运行效果:

![Mac](Mac.gif) ![iOS](Ios.landscape.gif)

在Android，嵌入式ARM Linux下的运行效果:

![Android](Android.gif) ![Linux](Linux.gif)

在Windows混合现实下的运行效果及开发者QQ群:

![Win MR](WinMR.gif) ![QQ group: 527251257](qq.group.jpg)

- GuiLite samples包括2个跨平台工程，一个是“Host monitor”，另一个是“Snake”；他们都是基于[GuiLite](https://github.com/idea4good/GuiLite)编写的实际应用，用来说明GuiLite的接口使用方法，并让你的程序同时运行在：iOS，Android，Linux，Windows，Mac平台上。
- GuiLite samples极易编译，在QQ开发群的帮助下，现在的编译通过率接近100%

## Host Monitor
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

## Snake
Snake只有200+行代码，用来解释如何绘制、渲染，通过对它的学习，你可以把GuiLite运行在单片机上。

[编译 "snake"](../Snake/README.md)

## 一些建议
是不是感觉很复杂？我们只是资质平庸的开发者，我们能做到的，你也可以！
- 敢于编译、运行
- 敢于修改代码
- 敢于开创自己的UI

## 代码镜像
[国内码云链接](https://gitee.com/idea4good/GuiLiteSamples)
