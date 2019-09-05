cmake_minimum_required(VERSION 2.8)

PROJECT(HelloWidgets)

ADD_EXECUTABLE(HelloWidgets
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloWidgets UIcode pthread dl)
