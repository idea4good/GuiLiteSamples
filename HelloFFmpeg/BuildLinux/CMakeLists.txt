cmake_minimum_required(VERSION 2.8)

PROJECT(HelloFFmpeg)

LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../UIcode/ffmpeg_lib/x86)

ADD_EXECUTABLE(HelloFFmpeg
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloFFmpeg UIcode pthread swscale avformat avcodec avutil z dl)
