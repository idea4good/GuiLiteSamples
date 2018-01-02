#ifndef native_hpp
#define native_hpp

#include <stdio.h>

#ifdef __cplusplus
extern "C"{
#endif
    
    void run_host_monitor();
    void* get_frame_buffer(int display_id, int* width, int* height);
    void mouse_down(int x, int y);
    void mouse_up(int x, int y);
    
#ifdef __cplusplus
}
#endif
#endif /* native_hpp */
