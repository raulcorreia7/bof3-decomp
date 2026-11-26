#include "engine/game/00/game_00.h"

/* K&R definition: the callers pass two arguments through the unprototyped
 * declaration, and the s16 parameters narrow here. stale_a3 arrives as the packed
 * probe word whose high half takes the tile y. */
/* FAKE: retail reads the row through a non-volatile pointer. */
/* func_8019C4F0 */
/* Returns whether one map cell stops the rock: off the map, a cliff, a drop or a solid cell code. */
MATCH s32 Actor_RockIsCellBlocked(x, y, stale_a2, stale_a3)
s16       x;
s16       y;
s32       stale_a2;
s32       stale_a3;
{
    Coord org;
    u8*   map;
    s16   ix;
    s16   iy;
    s16   dist;
    s32   tile;
    s16   counter;

    map = (u8*)MAP_BUNDLE_BASE;
    iy  = y;
    ix  = x;
    if (*(u16*)(iy * map[0] * 2 + g_AreaMapBundle.grid_offset * 4 + ix * 2 + map) == 0) {
        return 1;
    }
    stale_a3 &= HALF_MASK;
    stale_a3 |= (u16)y << 16;
    org.part.fraction = 0;
    org.part.integer  = x;
    dist              = Area_HeightSample(org.fixed, stale_a3 & 0xFFFF0000);
    tile              = Area_CellGetCode(ix, iy);
    counter           = COORD_INT(TASK(Actor)->pos.z);
    if (counter - dist < 257 && (tile & 0xF0) == 0xF0) {
        return 1;
    }
    counter = COORD_INT(TASK(Actor)->pos.z);
    if (counter == dist) {
        if ((tile & BYTE_MASK) == 0x10 || (tile & 0xF0) == 0x20 || (tile & 0xF0) == 0xA0) {
        found:
            return 1;
        }
        return 0;
    }
    if (counter < dist) {
        goto found;
    }
    return 0;
}
