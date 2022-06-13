//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

#include <stdio.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"{
#endif

    void startHello3Dwave(void* phy_fb, int width, int height, int color_bytes, struct DISPLAY_DRIVER* driver);
    void* getUiOfHello3Dwave(int* width, int* height, bool force_update);

#ifdef __cplusplus
}
#endif

