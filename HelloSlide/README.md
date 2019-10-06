# How to build for Win MFC?
## GuiLite.lib should be in BuildMFC\BuildMFC\libs\x86(x64), rebuild them if meet link error.
- Open "HelloSlide\BuildMFC\HelloSlide.sln" by Visual studio 2017
- Click `F5` to build/run `HelloSlide`

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloSlide`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HelloSlide /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window:
        1. `sudo su`
        2. `sudo ./xWindow 512 768 | ./HelloSlide shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabi gcc-arm-linux-gnueabi`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloSlide`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabi-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabi-g++" -D TARGET_ARCH="ARM" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloSlide to target Linux device
    - `chmod 777 HelloSlide`
    - `sudo ./HelloSlide /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer

## Q&A:
1. Could not display UI on Ubuntu with framebuffer
    - Enter pure command line mode(Ctrl + Alt + F1), and run again
    - Update Ubuntu to 18.10, and run again
2. Linking error: rebuild libGuiLite.a, and replace them in BuildLinux/libs
