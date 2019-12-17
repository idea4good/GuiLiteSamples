cmake_minimum_required(VERSION 2.8)

PROJECT(HelloStar)

ADD_EXECUTABLE(HelloStar
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloStar UIcode pthread dl)
