# How to port on any type of MCU?
## Prerequisite:
- You have a MCU project with enabled LCD source code
- Your project should implement function `void delay_ms(unsigned short nms)`, which would be used by core/src/adapter/api_none.cpp::thread_sleep

## Porting with Keil/IAR
![HowToPorting](HowToPorting.png)
1. Open your Keil/IAR project
2. Import all cpp files from `UIcode` in your project
3. Encapsulate draw piexel driver in `main.c`
4. Link your LCD driver with GuiLite, and call UI entry function(e.g, startHelloWave)
5. Build & Run with Keil/IAR

## Porting with ARM GCC
1. Repeat step 2~4 above
2. Open GuiLite.h, add a macro like this:
    ```c++
    #pragma once
    #define __none_os__ //Add this macro
    #define REAL_TIME_TASK_CYCLE_MS		50
    #define MAX(a,b) (((a)>(b))?(a):(b))
    ...
    ```
3. Build your MCU project with GCC
    - `cd HelloXXX`
    - `cmake -D CMAKE_C_COMPILER="/your-path/your-arm-gcc" -D CMAKE_CXX_COMPILER="/your-path/your-arm-g++" . && make`
    - result here: `BuildLinux/HelloXXX`