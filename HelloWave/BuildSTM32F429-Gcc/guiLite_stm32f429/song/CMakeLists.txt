include_directories(../main)
include_directories(../base)

aux_source_directory(. src)
add_library(song STATIC ${src})