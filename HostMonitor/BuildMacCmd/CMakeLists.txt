cmake_minimum_required(VERSION 2.8)

PROJECT(HostMonitor)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/libs)  

ADD_EXECUTABLE(HostMonitor
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HostMonitor UIcode GuiLite pthread dl)
