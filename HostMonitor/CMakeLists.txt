cmake_minimum_required(VERSION 2.8)

PROJECT(HostMonitor)

ADD_SUBDIRECTORY(UIcode)

if("${TARGET_OS}" STREQUAL "MAC")
	ADD_SUBDIRECTORY(BuildMacCmd)
else()
	ADD_SUBDIRECTORY(BuildLinux)
endif()
