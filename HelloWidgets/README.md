# How to build for Win MFC?
1. Open "HelloWidgets\BuildMFC\HelloWidgets.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloWidgets`

# How to build for Qt?
1. Open BuildQt/HelloWidgets.pro with Qt Creator
2. Build/Run with Qt Creator

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloWidgets`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu, Raspbian):
    - Run with framebuffer: `sudo ./HelloWidgets /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run with Qt display(x64): `sudo ./display-x64 1 680 512 | ./HelloWidgets shared-fb`
    - Run with Qt display(arm): `sudo ./display-arm  1 680 512 | ./HelloWidgets shared-fb`
    - The source code of display-xxx here: HostMonitor/BuildLinux/display.src
## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloWidgets`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloWidgets to target Linux device
    - `chmod 777 HelloWidgets`
    - `sudo ./HelloWidgets /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer
## Q&A:
1. Could not display UI on Ubuntu
    - Enter pure command line mode(Ctrl + Alt + F1), and run again
    - Update Ubuntu to 18.04, and run again