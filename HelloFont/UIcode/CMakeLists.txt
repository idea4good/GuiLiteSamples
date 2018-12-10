cmake_minimum_required(VERSION 2.8)

PROJECT(UIcode)

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/core_include
					${CMAKE_CURRENT_SOURCE_DIR}/gui_include)

FILE(GLOB SOURCE *.cpp)
FILE(GLOB RESOURCE resource/*.cpp)

ADD_LIBRARY(UIcode  ${SOURCE}
                    ${RESOURCE})

execute_process(
    COMMAND ${CMAKE_SOURCE_DIR}/.sync_build.sh HelloGuiLite
)
