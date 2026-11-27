#include "engine/game/00/game_00.h"

/* func_8019BF78 */
/* Saves the cell code under the rock and marks the cell 0x10. */
MATCH void Actor_RockClaimCell(void) {
    SELF(Actor)->param.unk_0B = (u8)Area_CellGetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y));
    Area_CellSetCode(COORD_INT(SELF(Actor)->pos.x), COORD_INT(SELF(Actor)->pos.y), 0x10);
}
