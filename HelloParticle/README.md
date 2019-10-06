# How to build for Win MFC?
## Prerequisite:
- GuiLite.lib should be in BuildMFC\BuildMFC\libs\x86(x64), ⚠️rebuild them if meet link error.

## Build
1. Open "HelloParticle\BuildMFC\HelloParticle.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloParticle`

# How to build for STM32F103 + ILI934x?
## Prerequisite:
- Install Keil uvsion 5.6 or above.
- GuiLite.lib should be in BuildSTM32F103-Keil\USER, ⚠️rebuild it if meet Linking error.
- Your hardware should be compatible with: Discovery kit/[正点原子开发板](https://item.taobao.com/item.htm?spm=a230r.1.14.20.17b441b9u49Ujg&id=582084489839&ns=1&abbucket=7#detail)/野火霸道开发板.
## Build
1. Open "HelloParticle\BuildSTM32F103-Keil\USER\HelloParticle.uvprojx" with Keil uvsion.
2. Choose your Device type(Default: STM32F103ZE) from option for target.
3. Build HelloParticle.
4. Connect your hardware with your host PC, and flash/run HEX file on it.

# How to port on any type of MCU?
## Prerequisite:
- You have Keil/IAR project which can enable LCD
- Your project should implement function `void delay_ms(unsigned short nms)`, which would be used by core/src/adapter/api_none.cpp::thread_sleep

## Porting with library
![HowToPorting](../doc/HowToPorting.png)
1. Open your MCU project(Keil/IAR), import GuiLite library - `GuiLite.lib`
2. Import all cpp files from `UIcode` in your project.
3. Encapsulate draw piexel driver in `main.c`
4. Link your LCD driver with GuiLite, and call UI entry function(e.g, startHelloParticle)
5. Build & Run ⚠️[rebuild `GuiLite.lib`](https://github.com/idea4good/GuiLite/blob/master/doc/HowToBuild.md) if meet Linking error, or your MCU do not compatible with STM32F103

## Porting with source code(⚠️maybe crash for some versions of Keil)
![HowToPorting](../doc/HowToPorting-1h1cpp.png)
1. Open your Keil/IAR project, and copy GuiLite.h/GuiLite-unknow.cpp built by [1h-1cpp.sh](https://github.com/idea4good/GuiLite/blob/master/doc/HowToBuild.md#option-2-header--source) to UIcode folder
2. Import all cpp files(⚠️except for GuiLite.h, GuiLite-unknow.cpp, because they have been included in UIcode.cpp) from `UIcode` in your project
3. Encapsulate draw piexel driver in `main.c`
4. Link your LCD driver with GuiLite, and call UI entry function(e.g, startHelloParticle)
5. Build & Run

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloParticle`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HelloParticle /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window:
        1. `sudo su`
        2. `sudo ./xWindow 240 320 | ./HelloParticle shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloParticle`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" -D TARGET_ARCH="ARM" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloParticle to target Linux device
    - `chmod 777 HelloParticle`
    - `sudo ./HelloParticle /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer

## Q&A:
1. Could not display UI on Ubuntu with framebuffer
    - Enter pure command line mode(Ctrl + Alt + F1), and run again
    - Update Ubuntu to 18.10, and run again
2. Linking error: rebuild libGuiLite.a, and replace them in BuildLinux/libs
