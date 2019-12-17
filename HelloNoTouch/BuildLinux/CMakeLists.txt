cmake_minimum_required(VERSION 2.8)

PROJECT(HelloNoTouch)

ADD_EXECUTABLE(HelloNoTouch
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloNoTouch UIcode pthread dl)
