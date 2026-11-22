#include "game_00.h"

/* The tile coordinate this pass walks is the high half of the work area's
 * 32-bit coordinate words (+0x36 of x.fixed, +0x3A of y.fixed); the
 * scratchpad result cells for offsets 1-5 collect the probe bytes.
 * two diagonal steps, and stores each move probe's result byte in its cell.
 */
MATCH void func_801BBBC8(s16 from_x, s16 from_y) {
    SP_REF(u8, 0x1u) = func_801BB2B8(from_x, from_y, COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x2u) = func_801BB2B8(COORD_INT(TASK(Actor)->pos.x), from_y, COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x3u) = func_801BB2B8(from_x, COORD_INT(TASK(Actor)->pos.y), COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x4u) = func_801BB2B8((s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), from_y, (s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x5u) = func_801BB2B8(from_x, (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1), COORD_INT(TASK(Actor)->pos.x), (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1));
}
