cmake_minimum_required(VERSION 2.8)

PROJECT(Hello3Ddonut)

ADD_EXECUTABLE(Hello3Ddonut
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(Hello3Ddonut UIcode pthread dl)
