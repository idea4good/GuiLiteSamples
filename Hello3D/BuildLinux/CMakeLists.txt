cmake_minimum_required(VERSION 2.8)

PROJECT(Hello3D)

ADD_EXECUTABLE(Hello3D
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(Hello3D UIcode pthread dl)
