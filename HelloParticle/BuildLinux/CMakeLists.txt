cmake_minimum_required(VERSION 2.8)

PROJECT(HelloParticle)

ADD_EXECUTABLE(HelloParticle
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloParticle UIcode pthread dl)
