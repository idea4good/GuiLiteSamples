cmake_minimum_required(VERSION 2.8)

PROJECT(HelloMolecule)

ADD_EXECUTABLE(HelloMolecule
			main.cpp
			std_io.cpp)
TARGET_LINK_LIBRARIES(HelloMolecule UIcode pthread dl)
