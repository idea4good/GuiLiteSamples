cmake_minimum_required(VERSION 3.5)
PROJECT(App)

enable_language(ASM)

set(CMAKE_SYSTEM_NAME  Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)


set (CMAKE_C_COMPILER "arm-none-eabi-gcc")
set (CMAKE_C_AR "arm-none-eabi-ar")
set (CMAKE_ASM_COMPILER "arm-none-eabi-gcc")
set (CMAKE_CXX_COMPILER "arm-none-eabi-g++")

# CFLAGS
set (CMAKE_C_FLAGS "-g -mthumb -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -std=gnu99 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "c compiler flags")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -D STM32F429xx")

# CXXFLAGS
set (CMAKE_CXX_FLAGS "-g -mthumb -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -std=c++11 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "cxx compiler flags")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -D STM32F429xx")
# ASMFLAGS
set (CMAKE_ASM_FLAGS "-g -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")

# LDFLAGS
set (CMAKE_EXE_LINKER_FLAGS "  -g -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mabi=aapcs" CACHE INTERNAL "executable linker flags")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${PROJECT_SOURCE_DIR}/tools/STM32F429ZITx_FLASH.ld")

add_subdirectory(base)
add_subdirectory(main)
add_subdirectory(gui)
add_subdirectory(song)











