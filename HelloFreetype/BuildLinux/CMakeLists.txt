cmake_minimum_required(VERSION 2.8)

PROJECT(HelloFreetype)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)

ADD_EXECUTABLE(HelloFreetype
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloFreetype UIcode pthread dl freetype z)
