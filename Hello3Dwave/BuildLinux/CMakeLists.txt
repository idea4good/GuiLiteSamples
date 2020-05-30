cmake_minimum_required(VERSION 2.8)

PROJECT(Hello3Dwave)

ADD_EXECUTABLE(Hello3Dwave
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(Hello3Dwave UIcode pthread dl)
