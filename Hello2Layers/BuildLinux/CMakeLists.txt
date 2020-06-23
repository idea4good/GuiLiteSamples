cmake_minimum_required(VERSION 2.8)

PROJECT(Hello2Layers)

ADD_EXECUTABLE(Hello2Layers
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(Hello2Layers UIcode pthread dl)
