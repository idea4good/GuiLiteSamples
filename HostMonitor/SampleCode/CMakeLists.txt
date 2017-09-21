cmake_minimum_required(VERSION 2.8)

PROJECT(Sample)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/core_include
					${CMAKE_CURRENT_SOURCE_DIR}/gui_include
					${CMAKE_CURRENT_SOURCE_DIR}/include)

ADD_SUBDIRECTORY(source)
