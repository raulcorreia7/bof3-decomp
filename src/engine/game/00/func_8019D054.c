#include "game_00.h"

MATCH bool func_8019D054(s32 point_x, s32 point_y) {
    s16 dist[4];
    s16 xi;
    s16 yi;
    s16 xp;
    s16 yp;
    s32 x;
    s32 y;
    s32 y2;
    s32 i;
    s32 index;

    x     = point_x;
    y     = point_y;
    index = Actor_FindInRange(x, y, 1) & BYTE_MASK;
    if (index != GAME_NONE) {
        g_Actors[index].interaction_flags |= ACTOR_FLAG_INTERACTION_PENDING;
    }
    x &= 0xFFFF0000;
    y &= 0xFFFF0000;
    xi = (s16)(x >> 16);
    yi = (y >> 16);
    if (func_8019D20C(xi, yi) & BYTE_MASK) {
        return true;
    }
    dist[0] = Area_SampleHeight(x, y);
    xp      = (xi + 1);
    if (func_8019D20C(xp, yi) & BYTE_MASK) {
        return true;
    }
    dist[1] = Area_SampleHeight(x + TO_COORD(1), y);
    yp      = (yi + 1);
    if (func_8019D20C(xi, yp) & BYTE_MASK) {
        return true;
    }
    y2      = y + TO_COORD(1);
    dist[2] = Area_SampleHeight(x, y2);
    if (func_8019D20C(xp, yp) & BYTE_MASK) {
        return true;
    }
    dist[3] = Area_SampleHeight(x + TO_COORD(1), y2);
    for (i = 1; i < 4; i++) {
        if (dist[0] != dist[i]) {
            return true;
        }
    }
    return false;
}
