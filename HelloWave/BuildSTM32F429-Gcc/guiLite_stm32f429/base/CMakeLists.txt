include_directories(../main)
aux_source_directory(. src)
add_library(base STATIC ${src} startup_stm32f429xx.s)
