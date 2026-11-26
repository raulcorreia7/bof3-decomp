#include "engine/game/00/game_00.h"

/* func_801C2AAC */
/* Starts the cell walk step when the actor stands on a cell of code 0xD0. */
MATCH s32 Party_StartCellWalk(void) {
    GAME_ARM_WORK_ON_CELL_HIT(0xD0, PARTY_MOVE_STEP_CELL_WALK);
}
