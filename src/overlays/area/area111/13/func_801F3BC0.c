#include "area111_13.h"

/* Walks the cell grid from the actor along its facing up to a wall cell and starts the slide over the cells crossed. */
MATCH void func_801F3BC0(void) {
    s8  x;
    s8  y;
    s8  offset;
    s32 facing;
    s32 nibble;
    u8  cell;

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
            nibble = D_801F5C18[y][x / 2] & 0xF;
        } else {
            nibble = D_801F5C18[y][x / 2] >> 4;
        }
        cell = nibble;
        if (cell == 0xF) {
            goto done;
        }
        /* The test leaves no code: it keeps the cell live past the wall test, which the bytes need. */
        if (cell != 0) {
            offset += 4;
        } else {
            offset += 4;
        }
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
