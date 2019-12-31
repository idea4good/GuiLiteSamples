cmake_minimum_required(VERSION 2.8)

PROJECT(HelloCircle)

ADD_EXECUTABLE(HelloCircle
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloCircle UIcode pthread dl)
