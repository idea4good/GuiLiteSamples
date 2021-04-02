# How to build for Win MFC?
1. Open "HelloJPG\BuildMFC\HelloJPG.sln" by Visual studio 2017
2. Click `F5` to build/run `HelloJPG`

# How to build for Linux?
## Compile & Run locally:
1. Compile:
    - `cd HelloJPG`
    - `cmake . && make`
    - `cd BuildLinux`
    - `chmod 777 *`
2. Run locally(e.g, Ubuntu):
    - Run with framebuffer: `sudo ./HelloJPG /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer device file.
    - Run inside X Window: `sudo ./xWindow 800 600 | ./HelloJPG shared-fb`

## Cross compiler & Run on target:
1. install compiler:
    - For ARM32: `sudo apt-get install g++-arm-linux-gnueabihf gcc-arm-linux-gnueabihf`
    - For ARM64: `sudo apt-get install g++-aarch64-linux-gnu gcc-aarch64-linux-gnu`
2. Cross compile:
    - `cd HelloJPG`
    - For ARM32: `cmake -D CMAKE_C_COMPILER="/usr/bin/arm-linux-gnueabihf-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/arm-linux-gnueabihf-g++" -D TARGET_ARCH="ARM" . && make`
    - For ARM64: `cmake -D CMAKE_C_COMPILER="/usr/bin/aarch64-linux-gnu-gcc" -D CMAKE_CXX_COMPILER="/usr/bin/aarch64-linux-gnu-g++" -D TARGET_ARCH="ARM" . && make`
3. Run on target Linux device:
    - Copy BuildLinux/HelloJPG to target Linux device
    - `chmod 777 HelloJPG`
    - `sudo ./HelloJPG /dev/fb0`&nbsp;&nbsp;&nbsp;&nbsp;/dev/fb0: The path of framebuffer
