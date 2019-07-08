cmake_minimum_required(VERSION 2.8)

PROJECT(Hello3D)

if("${TARGET_ARCH}" STREQUAL "ARM")
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs/arm)
else()
	LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)  
endif()

ADD_EXECUTABLE(Hello3D
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(Hello3D UIcode GuiLite pthread dl)
