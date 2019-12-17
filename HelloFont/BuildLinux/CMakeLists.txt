cmake_minimum_required(VERSION 2.8)

PROJECT(HelloFont)

ADD_EXECUTABLE(HelloFont
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloFont UIcode pthread dl)
