#include "game_00.h"
#include "sys/scratchpad.h"

/* Scratchpad map-coordinate staging: the staged halfwords at 0x04/0x06, their
 * per-axis bias flags at 0x08/0x0C and the source halfwords at 0x0A/0x0E. */

MATCH void func_801B13BC(void) {
    u16  value;
    s32  flag;
    u16* counter;
    u16  value2;
    s32  flag2;
    s16* counter2;

    value    = g_ScratchPad.cells.ray.shade.g;
    flag     = g_ScratchPad.cells.halves[4];
    counter  = &D_1F800004;
    *counter = value;
    if ((flag != 0) && (g_FacingOffsets[SELF(Actor)->direction].x > 0)) {
        *counter = value + 1;
    }
    value2    = D_1F80000E;
    flag2     = D_1F80000C;
    counter2  = &D_1F800006;
    *counter2 = value2;
    if ((flag2 != 0) && (g_FacingOffsets[SELF(Actor)->direction].y > 0)) {
        *counter2 = value2 + 1;
    }
}
