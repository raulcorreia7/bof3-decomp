#include "area077_14.h"

MATCH void func_801F36E8(s32 x, s32 y) {
    RECT rect;

    rect.x = x + 4;
    rect.y = y + 4;
    rect.w = 64;
    rect.h = 64;
    GFX_AddBlendDrawMode(1);
    if (D_800E4800 >= rect.x && D_800E4800 < rect.x + rect.w) {
        func_801F3B48((void*)AREA_WORK, 128);
    }
    func_801F3778(72, (void*)AREA_WORK, &rect);
}
