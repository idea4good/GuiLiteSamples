cmake_minimum_required(VERSION 2.8)

PROJECT(UIcode)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/core_include
					${CMAKE_CURRENT_SOURCE_DIR}/widgets_include
					${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(source)

execute_process(
    COMMAND ${CMAKE_SOURCE_DIR}/.sync_build.sh HostMonitor
)
