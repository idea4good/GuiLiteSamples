cmake_minimum_required(VERSION 2.8)

PROJECT(HelloMario)

ADD_EXECUTABLE(HelloMario
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloMario UIcode pthread dl)
