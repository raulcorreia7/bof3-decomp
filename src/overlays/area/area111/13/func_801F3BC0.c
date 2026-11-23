#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3BC0(void) {
    s8  x;
    s8  y;
    s8  offset;
    s32 facing;
    u8  value;

    offset = 0;
    x      = (u32)(TASK(Actor)->pos.x.part.integer - 11) >> 1;
    y      = (u32)(TASK(Actor)->pos.y.part.integer - 177) >> 1;
    facing = (TASK(Actor)->direction & 7) * 2;
    for (;;) {
        if ((u8)(x += D_80181B00[facing]) >= 7) {
            goto done;
        }
        if ((u8)(y += D_80181B01[facing]) >= 7) {
            goto done;
        }
        if (x & 1) {
            value = D_801F5C18[y][x / 2] & 0xF;
        } else {
            value = D_801F5C18[y][x / 2] >> 4;
        }
        if (value == 0xF) {
            goto done;
        }
        offset += 4;
    }
done:
    if (offset != 0) {
        g_ScriptState->steps = offset + 1;
        Area_SetFacingOffsetX(TASK(Actor)->direction);
        g_AreaCameraHeightDelta = 0;
        g_ScriptState->flags |= 0x40;
        TASK(Actor)->vz               = 0;
        COORD_INT(TASK(Actor)->pos.z) = -0x500;
    }
}
#else
INCLUDE_ASM(func_801F3BC0);
#endif
