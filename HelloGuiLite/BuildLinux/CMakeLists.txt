cmake_minimum_required(VERSION 2.8)

PROJECT(HelloGuiLite)

ADD_EXECUTABLE(HelloGuiLite
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloGuiLite UIcode pthread dl)
