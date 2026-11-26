#include "game_00.h"

#define BLOCKED(px, py, dir) (Area_HeightReadStep((px), (py), (dir)) >= 0x41 && ((u8*)&g_ScratchPad)[0])

MATCH s32 func_801C41D0(s32 pos_x, s32 pos_y, s16 probe_range) {
    Coord a;
    Coord b;

    s32 dist;
    s32 found;
    u16 saved;

    if (func_801C3E80(pos_x, pos_y, 1) & BYTE_MASK)
        return 1;
    b.part.integer  = (pos_y >> 16);
    a.part.integer  = (pos_x >> 16);
    a.part.fraction = 0x8000;
    b.part.fraction = 0x8000;
    if (BLOCKED(a.fixed, b.fixed, 4))
        return 1;
    a.part.fraction = 0x8000;
    b.part.fraction = 0;
    if (BLOCKED(a.fixed, b.fixed, 3))
        return 1;
    a.part.fraction = 0;
    b.part.fraction = 0x8000;
    if (BLOCKED(a.fixed, b.fixed, 5))
        return 1;
    if ((pos_x & 0xFFFF) == 0) {
        a.part.integer  = (pos_x >> 16) - 1;
        b.part.fraction = 0;
        a.part.fraction = 0x8000;
        b.part.integer  = (pos_y >> 16);
        if (BLOCKED(a.fixed, b.fixed, 7))
            return 1;
        b.part.integer = (pos_y >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 7))
            return 1;
        a.part.integer = (pos_x >> 16);
        b.part.integer = (pos_y >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 7))
            return 1;
        b.part.integer  = (pos_y >> 16);
        a.part.fraction = 0;
        a.part.integer  = (pos_x >> 16) - 1;
        b.part.fraction = 0x8000;
        if (BLOCKED(a.fixed, b.fixed, 1))
            return 1;
        a.part.integer = (pos_x >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 1))
            return 1;
    }
    if ((pos_y & 0xFFFF) == 0) {
        b.part.integer  = (pos_y >> 16) - 1;
        a.part.fraction = 0;
        b.part.fraction = 0x8000;
        a.part.integer  = (pos_x >> 16);
        if (BLOCKED(a.fixed, b.fixed, 1))
            return 1;
        a.part.integer = (pos_x >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 1))
            return 1;
        b.part.integer = (pos_y >> 16);
        a.part.integer = (pos_x >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 1))
            return 1;
        a.part.integer  = (pos_x >> 16);
        b.part.fraction = 0;
        a.part.fraction = 0x8000;
        b.part.integer  = (pos_y >> 16) - 1;
        if (BLOCKED(a.fixed, b.fixed, 3))
            return 1;
        b.part.integer = (pos_y >> 16) + 1;
        if (BLOCKED(a.fixed, b.fixed, 3))
            return 1;
    }
    if ((pos_x & 0xFFFF) == 0 && (pos_y & 0xFFFF) == 0) {
        a.part.fraction = 0;
        a.part.integer  = (pos_x >> 16) - 1;
        b.part.fraction = 0;
        b.part.integer  = (pos_y >> 16) - 1;
        if (BLOCKED(a.fixed | 0x8000, b.fixed | 0x8000, 0))
            return 1;
    }
    dist = Area_HeightRead(pos_x, pos_y) - probe_range;
    dist = ABS(dist);
    if (dist < 193) {
        saved                         = COORD_INT(SELF(Actor)->pos.z);
        COORD_INT(SELF(Actor)->pos.z) = (u16)probe_range;
        found                         = ~Actor_FindInRange(pos_x, pos_y, 1) != 0;
        COORD_INT(SELF(Actor)->pos.z) = saved;
        return found;
    }
    return 1;
}
