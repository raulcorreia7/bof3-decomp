#include "game_00.h"

/* Packed 16.16 coordinate word: the high half is the tile coordinate and the
 * low half the sub-tile bits, the layout func_801A8F94 stores. */
typedef union {
    s32 word;

    struct {
        u16 frac;
        s16 tile;
    } parts;
} GamePackedCoord;

/* K&R definition: the callers pass two arguments through the unprototyped
 * declaration, and the s16 parameters narrow here. stale_a3 arrives as the packed
 * probe word whose high half takes the tile y. */
/* FAKE: retail reads the row through a non-volatile pointer. */
MATCH s32 func_8019C4F0(x, y, stale_a2, stale_a3)
s16       x;
s16       y;
s32       stale_a2;
s32       stale_a3;
{
    GamePackedCoord org;
    u8*             map;
    s16             ix;
    s16             iy;
    s16             dist;
    s32             tile;
    s16             counter;

    map = (u8*)MAP_BUNDLE_BASE;
    iy  = y;
    ix  = x;
    if (*(u16*)(iy * map[0] * 2 + D_80104002 * 4 + ix * 2 + map) == 0) {
        return 1;
    }
    stale_a3 &= 0xFFFF;
    stale_a3 |= (u16)y << 16;
    org.parts.frac = 0;
    org.parts.tile = x;
    dist           = Area_SampleHeight(org.word, stale_a3 & 0xFFFF0000);
    tile           = Area_GetCellCode(ix, iy);
    counter        = COORD_INT(((Actor*)SCRATCH_WORK)->pos.z);
    if (counter - dist < 257 && (tile & 0xF0) == 0xF0) {
        return 1;
    }
    counter = COORD_INT(((Actor*)SCRATCH_WORK)->pos.z);
    if (counter == dist) {
        if ((tile & 0xFF) == 0x10 || (tile & 0xF0) == 0x20 || (tile & 0xF0) == 0xA0) {
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
