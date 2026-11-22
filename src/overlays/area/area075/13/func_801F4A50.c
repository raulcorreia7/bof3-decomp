#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4A50(s32 x, s32 y, s32 width, s32 height, s32 mode) {
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_FIELD_SCENE, getTPage(0, 2, 320, 256));
    if (mode != 0) {
        return;
    }
    g_ScratchPadVectors[0].vx = x;
    g_ScratchPadVectors[0].vy = y;
    g_ScratchPadVectors[1].vx = x + width;
    g_ScratchPadVectors[1].vy = y + height;
}
#else
INCLUDE_ASM(func_801F4A50);
#endif
