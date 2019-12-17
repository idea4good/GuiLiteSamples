cmake_minimum_required(VERSION 2.8)

PROJECT(HelloSlide)

ADD_EXECUTABLE(HelloSlide
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloSlide UIcode pthread dl)
