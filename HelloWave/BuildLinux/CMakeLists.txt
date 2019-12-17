cmake_minimum_required(VERSION 2.8)

PROJECT(HelloWave)

ADD_EXECUTABLE(HelloWave
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloWave UIcode pthread dl)
