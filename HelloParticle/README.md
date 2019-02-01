## How to build for Win MFC?
### Prerequisite:
- core.lib gui.lib should be in BuildMFC\BuildMFC\libs\x86(x64), ⚠️rebuild them if meet link error.
### Build
1. Open "HelloParticle\BuildMFC\HelloParticle.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloParticle`

## How to build for STM32F103 + ILI934x?
### Prerequisite:
- Install Keil uvsion 5.6 or above.
- GuiLite.lib should be in BuildSTM32F103-Keil\USER, ⚠️rebuild it if meet Linking error.
- Your hardware should be compatible with: Discovery kit/[正点原子开发板](https://item.taobao.com/item.htm?spm=a230r.1.14.20.17b441b9u49Ujg&id=582084489839&ns=1&abbucket=7#detail)/野火霸道开发板.
### Build
1. Open "HelloParticle\BuildSTM32F103-Keil\USER\HelloParticle.uvprojx" with Keil uvsion.
2. Choose your Device type(Default: STM32F103ZE) from option for target.
3. Build HelloParticle.
4. Connect your hardware with your host PC, and flash/run HEX file on it.

## How to port on any MCU?
### Prerequisite:
- You have Keil/IAR project which can enable LCD
- Your project should implement function `void delay_ms(unsigned short nms)`, which would be used by core/src/adapter/api_none.cpp::thread_sleep
### Porting
![HowToPorting](../doc/HowToPorting.png)
1. Open your MCU project(Keil/IAR), import GuiLite library - `GuiLite.lib`
2. Import all cpp files from `UIcode` in your project.
3. Encapsulate draw piexel driver in `main.c`
4. Link your LCD driver with GuiLite, and call UI entry function(e.g, startHelloParticle)
5. Build & Run ⚠️rebuild `GuiLite.lib` if meet Linking error.

## How to build for x64 Linux or Rasperry Pi?
### libcore.a libgui.a should be in BuildLinux\libs, ⚠️rebuild them if meet Linking error, e.g: -fPIC, libxxx not found.
1. Build target:
- `cd HelloParticle`
- `cmake .`
- `make`
- `cd BuildLinux`
- `chmod 777 *`

2. Run on Ubuntu:
- `sudo ./HelloParticle /dev/fb0`   /dev/fb0: The path of framebuffer device file.
- If meet **permission** issue, you should enter pure command mode(not desktop mode), and run it again.

3. Run inside QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- If x64:`sudo ./display-x64 1 240 320 | ./HelloParticle shared-fb`
- If raspberry pi:`sudo ./display-arm  1 240 320 | ./HelloParticle shared-fb`
- The source code of display-xxx here: HostMonitor/BuildLinux/display.src
