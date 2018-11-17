# GuiLite Samples - Do it yourself!
[中文](doc/README-cn.md)

Runs on Mac & iOS:

![Mac](doc/Mac.gif) ![iOS](doc/Ios.landscape.gif)

Runs on Android & ARM Linux embedded:

![Android](doc/Android.gif) ![Linux](doc/Linux.gif)

Runs on Windows Mixed Reality & QQ developers' group:

![Win MR](doc/WinMR.gif) ![QQ group: 527251257](doc/qq.group.jpg)

- GuiLite samples contain 2 cross-platform projects. One is *Host Monitor* while the other is *Snake*. They are both based on [GuiLite](https://github.com/idea4good/GuiLite). They show you how to use GuiLite's interface, and how GuiLite works on iOS, Android, GNU/Linux, Windows and macOS platform.
- GuiLite samples are easy to compile & run. With the help of QQ group, you will pass the compiling nearly 100%.

## Host Monitor
Host Monitor has 2,000 lines of code related to UI, showing you how to layout UI, and customize/extend your UI widgets.
### Code Walkthrough
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

[UART on Android phone](doc/Serial.md)

[Download Android APP](http://zhushou.360.cn/detail/index/soft_id/1754231)
## Snake
Snake has only 200+ lines of code, showing you how to render. It will help you run GuiLite on MCU.

[Build "snake"](Snake/README.md)

## Suggestions
Looks complex? Trust me that you can do everything we did since we are ordinary guys.
- Dare to build
- Dare to make modification
- Dare to create your UI framework

## Repository Mirror
[Link to Gitee in China](https://gitee.com/idea4good/GuiLiteSamples)
