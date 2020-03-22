cmake_minimum_required(VERSION 2.8)

PROJECT(HelloTransparent)

ADD_EXECUTABLE(HelloTransparent
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloTransparent UIcode pthread dl)
