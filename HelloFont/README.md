## How to build for Win MFC?
### GuiLite.lib should be in BuildMFC\BuildMFC\libs\x86(x64), rebuild them if meet link error.
- Open "HelloFont\BuildMFC\HelloFont.sln" by Visual studio 2017
- Click `F5` to build/run `HelloFont`

## How to build for Linux(x64/ARM/Raspberry Pi)?
### Install cross compiler:
- For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
- For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
### Build & Run:
1. Build:
- `cd HelloFont`
- If x64: `cmake .`
- If raspberry pi: `cmake -D TARGET_ARCH="ARM" .`
- If ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" -D TARGET_ARCH="ARM" .`
- If ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" .`
- `make`
- `cd BuildLinux`
- `chmod 777 *`

2. Run with framebuffer:
- `sudo ./HelloFont /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.

3. Run inside QT APP(display-xxx is a QT APP for display, skip this if you haven't installed QT):
- If x64: `sudo ./display-x64 1 1400 580 | ./HelloFont shared-fb`
- If ARM/Raspberry Pi: `sudo ./display-arm  1 1400 580 | ./HelloFont shared-fb`
- The source code of display-xxx here: HostMonitor/BuildLinux/display.src

### Q&A:
1. Meet linking error(e.g: -fPIC, libxxx not found)
- If x64: rebuild libGuiLite.a, and replace them in BuildLinux/libs
- If ARM: rebuild libGuiLite.a, and replace them in BuildLinux/libs/arm
2. How to run HelloFont on ARM Linux device?
- Copy HelloFont you build on ARM Linux device
- `sudo ./HelloFont /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer
3. Could not display UI on Ubuntu
- Update Ubuntu to 18.04, and run again
- Enter pure command line mode, and run again