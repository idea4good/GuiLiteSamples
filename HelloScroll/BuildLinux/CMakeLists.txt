cmake_minimum_required(VERSION 2.8)

PROJECT(HelloScroll)

ADD_EXECUTABLE(HelloScroll
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloScroll UIcode pthread dl)
