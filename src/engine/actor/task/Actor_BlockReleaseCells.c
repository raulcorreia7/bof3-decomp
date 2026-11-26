#include "engine/game/00/game_00.h"

/* func_8019D4BC */
/* Writes back the saved cell codes under the block. */
MATCH void Actor_BlockReleaseCells(void) {
    Area_HeightSet(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0);
    Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), FIELD(u8, g_Self, 0x14u));
    if (COORD_FRAC(SELF(Actor)->pos.x) != 0) {
        Area_HeightSet((s16)(COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y), 0);
        Area_CellSetCode((s16)(COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y), FIELD(u8, g_Self, 0x15u));
    }
    if (COORD_FRAC(SELF(Actor)->pos.y) != 0) {
        Area_HeightSet(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1), 0);
        Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1), FIELD(u8, g_Self, 0x16u));
    }
    if ((COORD_FRAC(SELF(Actor)->pos.x) != 0) && (COORD_FRAC(SELF(Actor)->pos.y) != 0)) {
        Area_HeightSet((s16)(COORD_INT(SELF(Actor)->pos.x) + 1), (s16)(COORD_INT(SELF(Actor)->pos.y) + 1), 0);
        Area_CellSetCode((s16)(COORD_INT(SELF(Actor)->pos.x) + 1), (s16)(COORD_INT(SELF(Actor)->pos.y) + 1), FIELD(u8, g_Self, 0x17u));
    }
}
