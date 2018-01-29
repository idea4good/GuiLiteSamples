# GuiLite Samples - Do it yourself!
Runs on Mac & iOS:

![Mac](doc/Mac.gif) ![iOS](doc/Ios.landscape.gif)

Runs on Android & ARM Linux embeded:

![Android](doc/Android.gif) ![Linux](doc/Linux.gif)

Runs on Windows Mixed Reality & QQ developers group:

![Win MR](doc/WinMR.gif) ![QQ group: 527251257](doc/qq.group.jpg)

[中文](doc/README-cn.md)

- GuiLite samples has 2 cross platform projects. one is "host monitor", the other is "snake"; they all base on [GuiLite](https://github.com/idea4good/GuiLite), they show you how to use GuiLite interface, and how GuiLite works on iOS, Android, Linux, Windows, Mac platform.
- GuiLite samples are easy to compile & run. With the help of QQ group, you will pass the compiling nearly 100%

## Host Monitor
HostMonitor has 2,000 lines code related to UI, will show you how to layout UI, and customize/extend your UI widgets.
### Code walkthrough
- HostMonitor\SampleCode\source\ui_tree: **Layout UI**
- HostMonitor\SampleCode\source\ui_ctrl_ex: **Customize your widgets**

### Cross platform
- HostMonitor\BuildAndroid: **Java code, for Android**
- HostMonitor\BuildIOS: **Swift code, for iOS**
- HostMonitor\BuildLinux: **C code, for Linux**
- HostMonitor\BuildWin32: **C code, for Windows command mode**
- HostMonitor\BuildUWP: **CX code, for UWP(include Mixed/Virtual Reality)**
- HostMonitor\BuildMacCmd: **Swift code, for Mac command mode**
- HostMonitor\BuildMacCocoa: **Swift code, for Mac APP with UI**

[Build "host monitor"](HostMonitor/README.md)

## Snake
Snake has only 200+ lines code, will show you how to render. It will help you run GuiLite on MCU.

[Build "snake"](Snake/README.md)

## Suggestions
Looks complex? Trust me, We're normal guys, you can do everything we do.
- Dare to build
- Dare to modification
- Dare to create your UI framework

## Repository Mirror
[Link to Gitee in China](https://gitee.com/idea4good/GuiLiteSamples)