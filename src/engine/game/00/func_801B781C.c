#include "game_00.h"

MATCH void func_801B781C(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0 && (func_801C2AAC() & BYTE_MASK) == 0) {
        Script_Request(TASK(Actor)->direction);
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
    }
}
