FILE(GLOB START start/*.cpp)

ADD_LIBRARY(sample ${START})
				
TARGET_LINK_LIBRARIES(sample core gui)