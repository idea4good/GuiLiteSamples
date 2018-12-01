cmake_minimum_required(VERSION 2.8)

PROJECT(HelloGuiLite)

ADD_SUBDIRECTORY(UIcode)

if("${TARGET_OS}" STREQUAL "MAC")
	ADD_SUBDIRECTORY(BuildMacCmd)
else()
	ADD_SUBDIRECTORY(BuildLinux)
endif()
