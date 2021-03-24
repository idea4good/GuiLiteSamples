cmake_minimum_required(VERSION 2.8)

if("${TARGET_ARCH}" STREQUAL "ARM")
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../UIcode/libs/arm)
else()
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../UIcode/libs/x86)	
endif()

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)

ADD_EXECUTABLE(HelloFreetype
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloFreetype UIcode pthread dl freetype)
