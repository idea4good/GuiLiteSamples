## How to build for Win MFC?
1. Open "HelloFreetype\BuildMFC\HelloFreetype.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloFreetype`

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloFreetype`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HelloFreetype /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window: `sudo ./xWindow 1400 580 | ./HelloFreetype shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloFreetype`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloFreetype to target Linux device
    - `chmod 777 HelloFreetype`
    - `sudo ./HelloFreetype /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer
