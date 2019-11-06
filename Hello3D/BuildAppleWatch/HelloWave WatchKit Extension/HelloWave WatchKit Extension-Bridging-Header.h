//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

#include <stdio.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"{
#endif

    void startHello3D(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);
    void* getUiOfHello3D(int* width, int* height, bool force_update);

#ifdef __cplusplus
}
#endif

