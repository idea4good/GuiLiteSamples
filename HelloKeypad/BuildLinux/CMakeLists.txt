cmake_minimum_required(VERSION 2.8)

PROJECT(HelloKeypad)

ADD_EXECUTABLE(HelloKeypad
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloKeypad UIcode pthread dl)
