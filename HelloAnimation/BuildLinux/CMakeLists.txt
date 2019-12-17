cmake_minimum_required(VERSION 2.8)

PROJECT(HelloAnimation)

ADD_EXECUTABLE(HelloAnimation
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloAnimation UIcode pthread dl)
