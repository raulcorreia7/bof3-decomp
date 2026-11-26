#include "engine/game/00/game_00.h"

/* func_801C2B4C */
/* Starts the fall step when the actor stands on a cell of code 0xA4. */
MATCH s32 Party_StartFallThrough(void) {
    GAME_ARM_WORK_ON_CELL_HIT(0xA4, PARTY_MOVE_STEP_FALL_THROUGH);
}
