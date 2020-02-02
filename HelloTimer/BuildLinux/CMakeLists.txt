cmake_minimum_required(VERSION 2.8)

PROJECT(HelloTimer)

ADD_EXECUTABLE(HelloTimer
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloTimer UIcode pthread dl)
