#include "engine/game/00/game_00.h"

/* func_8019D270 */
/* Saves the codes of the cells under the block and marks them 0x11. */
MATCH void Actor_BlockClaimCells(void) {
    Area_HeightSet((s32)COORD_INT(SELF(Actor)->pos.x), (s32)COORD_INT(SELF(Actor)->pos.y), 0x10U);
    SELF(Actor)->vz = (s32)(Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK);
    Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0x11);
    if (COORD_FRAC(SELF(Actor)->pos.x) != 0) {
        Area_HeightSet((s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s32)COORD_INT(SELF(Actor)->pos.y), 0x10U);
        SELF(Actor)->vz = (s32)(SELF(Actor)->vz | ((Area_CellGetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y)) & BYTE_MASK) << 8));
        Area_CellSetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), COORD_INT(SELF(Actor)->pos.y), 0x11);
    }
    if (COORD_FRAC(SELF(Actor)->pos.y) != 0) {
        Area_HeightSet((s32)COORD_INT(SELF(Actor)->pos.x), (s32)(s16)(*(u16*)&COORD_INT(SELF(Actor)->pos.y) + 1), 0x10U);
        SELF(Actor)->vz = (s32)(SELF(Actor)->vz | ((Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1)) & BYTE_MASK) << 0x10));
        Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1), 0x11);
    }
    if ((COORD_FRAC(SELF(Actor)->pos.x) != 0) && (COORD_FRAC(SELF(Actor)->pos.y) != 0)) {
        Area_HeightSet((s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s32)(s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1), 0x10U);
        SELF(Actor)->vz = (s32)(SELF(Actor)->vz | (Area_CellGetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1)) << 0x18));
        Area_CellSetCode((s16)((u16)COORD_INT(SELF(Actor)->pos.x) + 1), (s16)((u16)COORD_INT(SELF(Actor)->pos.y) + 1), 0x11);
    }
}
