cmake_minimum_required(VERSION 2.8)

PROJECT(HelloAnimation)

if("${TARGET_ARCH}" STREQUAL "ARM")
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/arm)
else()
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)  
endif()

ADD_EXECUTABLE(HelloAnimation
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloAnimation UIcode GuiLite pthread dl)
