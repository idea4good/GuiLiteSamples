cmake_minimum_required(VERSION 2.8)

PROJECT(HelloPendulum)

ADD_EXECUTABLE(HelloPendulum
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloPendulum UIcode pthread dl)
