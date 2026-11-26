#include "engine/game/00/game_00.h"

/* Probes the five neighbouring cells of the actor's tile and stores each result byte in scratchpad cells 1 to 5. */
/* func_801BBBC8 */
MATCH void Area_WalkProbeCells(s16 from_x, s16 from_y) {
    SP_REF(u8, 0x1u) = func_801BB2B8(from_x, from_y, COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x2u) = func_801BB2B8(COORD_INT(TASK(Actor)->pos.x), from_y, COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x3u) = func_801BB2B8(from_x, COORD_INT(TASK(Actor)->pos.y), COORD_INT(TASK(Actor)->pos.x), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x4u) = func_801BB2B8((s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), from_y, (s16)((u16)COORD_INT(TASK(Actor)->pos.x) + 1), COORD_INT(TASK(Actor)->pos.y));
    SP_REF(u8, 0x5u) = func_801BB2B8(from_x, (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1), COORD_INT(TASK(Actor)->pos.x), (s16)((u16)COORD_INT(TASK(Actor)->pos.y) + 1));
}
