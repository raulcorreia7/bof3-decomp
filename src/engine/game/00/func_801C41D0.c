#include "game_00.h"

#define BLOCKED(px, py, dir) (Area_ReadStepHeight((px), (py), (dir)) >= 0x41 && ((u8*)&g_ScratchPad)[0])

#ifdef NON_MATCHING
NON_MATCHING s32 func_801C41D0(s32 pos_x, s32 pos_y, s16 probe_range) {
    s32 a;
    s32 b;
    s32 dist;
    s32 found;
    u16 saved;

    if (func_801C3E80(pos_x, pos_y, 1) & BYTE_MASK)
        return 1;
    a = (((u32)pos_x >> 16) << 16) | 0x8000;
    b = (((u32)pos_y >> 16) << 16) | 0x8000;
    if (BLOCKED(a, b, 4))
        return 1;
    a &= 0xFFFF0000;
    a |= 0x8000;
    b &= 0xFFFF0000;
    if (BLOCKED(a, b, 3))
        return 1;
    a &= 0xFFFF0000;
    b &= 0xFFFF0000;
    b |= 0x8000;
    if (BLOCKED(a, b, 5))
        return 1;
    if ((pos_x & HALF_MASK) == 0) {
        a = (((pos_x >> 16) - 1) << 16) | 0x8000;
        b = ((u32)pos_y >> 16) << 16;
        if (BLOCKED(a, b, 7))
            return 1;
        b = (b & HALF_MASK) | (((pos_y >> 16) + 1) << 16);
        if (BLOCKED(a, b, 7))
            return 1;
        a = (a & HALF_MASK) | (((u32)pos_x >> 16) << 16);
        b = (b & HALF_MASK) | (((pos_y >> 16) + 1) << 16);
        if (BLOCKED(a, b, 7))
            return 1;
        a = ((pos_x >> 16) - 1) << 16;
        b = (((u32)pos_y >> 16) << 16) | 0x8000;
        if (BLOCKED(a, b, 1))
            return 1;
        a = (a & HALF_MASK) | (((pos_x >> 16) + 1) << 16);
        if (BLOCKED(a, b, 1))
            return 1;
    }
    if ((pos_y & HALF_MASK) == 0) {
        b = (((pos_y >> 16) - 1) << 16) | 0x8000;
        a = ((u32)pos_x >> 16) << 16;
        if (BLOCKED(a, b, 1))
            return 1;
        a = (a & HALF_MASK) | (((pos_x >> 16) + 1) << 16);
        if (BLOCKED(a, b, 1))
            return 1;
        b = (b & HALF_MASK) | (((u32)pos_y >> 16) << 16);
        a = (a & HALF_MASK) | (((pos_x >> 16) + 1) << 16);
        if (BLOCKED(a, b, 1))
            return 1;
        a = (((u32)pos_x >> 16) << 16) | 0x8000;
        b = ((pos_y >> 16) - 1) << 16;
        if (BLOCKED(a, b, 3))
            return 1;
        b = (b & HALF_MASK) | (((pos_y >> 16) + 1) << 16);
        if (BLOCKED(a, b, 3))
            return 1;
    }
    if ((pos_x & HALF_MASK) == 0 && (pos_y & HALF_MASK) == 0) {
        a = ((pos_x >> 16) - 1) << 16;
        b = ((pos_y >> 16) - 1) << 16;
        if (BLOCKED(a | 0x8000, b | 0x8000, 0))
            return 1;
    }
    dist = Area_ReadHeight(pos_x, pos_y) - probe_range;
    dist = ABS(dist);
    if (dist < 193) {
        saved                    = COORD_INT(g_Task->pos.z);
        COORD_INT(g_Task->pos.z) = (u16)probe_range;
        found                    = ~Actor_FindInRange(pos_x, pos_y, 1) != 0;
        COORD_INT(g_Task->pos.z) = saved;
        return found;
    }
    return 1;
}
#else
INCLUDE_ASM(func_801C41D0);
#endif
