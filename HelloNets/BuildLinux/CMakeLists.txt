cmake_minimum_required(VERSION 2.8)

PROJECT(HelloNets)

ADD_EXECUTABLE(HelloNets
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloNets UIcode pthread dl)
