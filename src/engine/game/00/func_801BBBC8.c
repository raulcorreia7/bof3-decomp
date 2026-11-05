#include "game_00.h"

/* The tile coordinate this pass walks is the high half of the work area's
 * 32-bit coordinate words (+0x36 of x.fixed, +0x3A of y.fixed); the
 * scratchpad result cells for offsets 1-5 collect the probe bytes.
 * two diagonal steps, and stores each move probe's result byte in its cell.
 */
MATCH void func_801BBBC8(s16 from_x, s16 from_y) {
    SP_REF(u8, 0x1u) = func_801BB2B8(from_x, from_y, g_Task->x.part.integer, g_Task->y.part.integer);
    SP_REF(u8, 0x2u) = func_801BB2B8(g_Task->x.part.integer, from_y, g_Task->x.part.integer, g_Task->y.part.integer);
    SP_REF(u8, 0x3u) = func_801BB2B8(from_x, g_Task->y.part.integer, g_Task->x.part.integer, g_Task->y.part.integer);
    SP_REF(u8, 0x4u) = func_801BB2B8((s16)((u16)g_Task->x.part.integer + 1), from_y,
                                     (s16)((u16)g_Task->x.part.integer + 1), g_Task->y.part.integer);
    SP_REF(u8, 0x5u) = func_801BB2B8(from_x, (s16)((u16)g_Task->y.part.integer + 1), g_Task->x.part.integer,
                                     (s16)((u16)g_Task->y.part.integer + 1));
}
