cmake_minimum_required(VERSION 2.8)

PROJECT(SampleNative)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)  

ADD_EXECUTABLE(sample_native
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(sample_native sample gui core pthread dl)
