cmake_minimum_required(VERSION 2.8)

PROJECT(HelloFFmpeg)

if("${TARGET_ARCH}" STREQUAL "ARM")
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../UIcode/ffmpeg_lib/arm)
else()
	LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../UIcode/ffmpeg_lib/x86)	
endif()

ADD_EXECUTABLE(HelloFFmpeg
			main.cpp
			std_io.cpp)

if("${TARGET_ARCH}" STREQUAL "ARM")
	TARGET_LINK_LIBRARIES(HelloFFmpeg UIcode pthread swscale avformat avcodec avutil)
else()
	TARGET_LINK_LIBRARIES(HelloFFmpeg UIcode pthread swscale avformat avcodec avutil z dl)
endif()
