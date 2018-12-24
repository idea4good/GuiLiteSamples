## How to build for Win MFC?
### core.lib gui.lib should be in BuildMFC\BuildMFC\libs\x86(x64), rebuild them if meet link error.
- Open "HelloAnimation\BuildMFC\HelloAnimation.sln" by Visual studio 2017
- Click `F5` to build/run `HelloAnimation`

## How to build for ARM Linux device?
### libcore.a libgui.a should be in BuildLinux\libs\arm, ⚠️rebuild them if meet Linking error, e.g: -fPIC, libxxx not found.
### Install cross compiler:
- For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
- For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
### Build
- `cd HelloAnimation`
- For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" -D TARGET_ARCH="ARM" .`
- For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" .`
- `make`
- `cd BuildLinux`
- `chmod 777 *`
- `sudo ./HelloAnimation /dev/fb0`   /dev/fb0: The path of framebuffer device file.

## How to build for x64 Linux or Rasperry Pi?
### libcore.a libgui.a should be in BuildLinux\libs, ⚠️rebuild them if meet Linking error, e.g: -fPIC, libxxx not found.
1. Build target:
- `cd HelloAnimation`
- `cmake .`
- `make`
- `cd BuildLinux`
- `chmod 777 *`

2. Run on Ubuntu:
- `sudo ./HelloAnimation /dev/fb0`   /dev/fb0: The path of framebuffer device file.
- If meet **permission** issue, you should enter pure command mode(not desktop mode), and run it again.

3. Run inside QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- If x64:`sudo ./display-x64 1 238 169 | ./HelloAnimation shared-fb`
- If raspberry pi:`sudo ./display-arm  1 238 169 | ./HelloAnimation shared-fb`
- The source code of display-xxx here: HostMonitor/BuildLinux/display.src
