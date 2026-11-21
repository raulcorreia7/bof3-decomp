#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3BC0(void) {
    s8 x;
    s8 y;
    s8 offset;
    u8 facing;
    u8 value;

    offset = 0;
    x      = (g_Task->pos.x.part.integer - 11) >> 1;
    y      = (g_Task->pos.y.part.integer - 177) >> 1;
    facing = g_Task->direction & 7;
    for (;;) {
        x += D_80181B00[facing * 2];
        if ((u8)x >= 7) {
            break;
        }
        y += D_80181B01[facing * 2];
        if ((u8)y >= 7) {
            break;
        }
        if (x & 1) {
            value = D_801F5C18[y][x / 2] & 0xF;
        } else {
            value = D_801F5C18[y][x / 2] >> 4;
        }
        if (value == 0xF) {
            break;
        }
        offset += 4;
    }
    if (offset) {
        g_ScriptState->steps = offset + 1;
        Area_SetFacingOffsetX(g_Task->direction);
        g_AreaCameraHeightStep = 0;
        g_ScriptState->flags |= 0x40;
        g_Task->vz               = 0;
        COORD_INT(g_Task->pos.z) = -0x500;
    }
}
#else
INCLUDE_ASM(func_801F3BC0);
#endif
