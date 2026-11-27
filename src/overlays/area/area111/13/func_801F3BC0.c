#include "area111_13.h"

/* Reads the grid cell at a column and row: two cells a byte, the even column in the high nibble. */
static inline s8 Area_SlideCell(s8 x, s8 y) {
    if (x & 1) {
        return D_801F5C18[y][x / 2] & 0xF;
    }
    return D_801F5C18[y][x / 2] >> 4;
}

/* Walks the cell grid from the actor along its facing up to a wall cell and starts the slide over the cells crossed. */
MATCH void func_801F3BC0(void) {
    s8  x;
    s8  y;
    s8  offset;
    s32 facing;

    offset = 0;
    x      = (u32)(SELF(Actor)->pos.x.part.integer - 11) >> 1;
    y      = (u32)(SELF(Actor)->pos.y.part.integer - 177) >> 1;
    facing = SELF(Actor)->direction & 7;
    for (;;) {
        if ((u8)(x += D_80181B00[facing][0]) >= 7) {
            goto done;
        }
        if ((u8)(y += D_80181B00[facing][1]) >= 7) {
            goto done;
        }
        if (Area_SlideCell(x, y) == 0xF) {
            goto done;
        }
        offset += 4;
    }
done:
    if (offset != 0) {
        g_ScriptState->steps = offset + 1;
        Area_SetFacingOffsetX(SELF(Actor)->direction);
        g_AreaCameraHeightDelta = 0;
        g_ScriptState->flags |= 0x40;
        SELF(Actor)->vz               = 0;
        COORD_INT(SELF(Actor)->pos.z) = -0x500;
    }
}
