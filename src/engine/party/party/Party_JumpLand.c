#include "engine/game/00/game_00.h"

/* func_801B781C */
/* Waits for the landing animation to end, then returns the actor to mode 1. */
MATCH void Party_JumpLand(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0 && (Party_StartCellWalk() & BYTE_MASK) == 0) {
        Script_Request(SELF(Actor)->direction);
        g_Game.current->u.field.mode.unsigned_value = 0;
        SELF(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        SELF(Actor)->unk_03 = 0;
    }
}
