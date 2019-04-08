cmake_minimum_required(VERSION 2.8)

PROJECT(HelloMario)

if("${TARGET_ARCH}" STREQUAL "ARM")
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/arm)
else()
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)  
endif()

ADD_EXECUTABLE(HelloMario
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloMario UIcode GuiLite pthread dl)
