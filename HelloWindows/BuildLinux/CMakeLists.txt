cmake_minimum_required(VERSION 2.8)

PROJECT(HelloWindows)

ADD_EXECUTABLE(HelloWindows
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloWindows UIcode pthread dl)
