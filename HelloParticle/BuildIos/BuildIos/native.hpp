#ifndef native_hpp
#define native_hpp

#include <stdio.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"{
#endif
    void run_hello_particle();
    void* get_ui_of_hello_particle(int* width, int* height, bool force_update);
#ifdef __cplusplus
}
#endif
#endif /* native_hpp */
