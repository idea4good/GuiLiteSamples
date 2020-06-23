cmake_minimum_required(VERSION 2.8)

PROJECT(HelloLayers)

ADD_EXECUTABLE(HelloLayers
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloLayers UIcode pthread dl)
