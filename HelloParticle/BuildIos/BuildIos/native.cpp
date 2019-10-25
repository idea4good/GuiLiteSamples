#include "native.hpp"
#include <stdlib.h>


extern "C" void startHelloParticle(void* phy_fb, int width, int height, int color_bytes, struct EXTERNAL_GFX_OP* gfx_op);
extern "C" void* getUiOfHelloParticle(int* width, int* height, bool force_update);

void run_hello_particle()
{
    startHelloParticle(calloc(240 * 320, 2), 240, 320, 2, NULL);
}

void* get_ui_of_hello_particle(int* width, int* height, bool force_update)
{
    return getUiOfHelloParticle(width, height, false);
}
