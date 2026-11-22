#include "game_00.h"

MATCH void func_801B781C(void) {
    if ((Script_AnimStepOnce() & BYTE_MASK) != 0 && (func_801C2AAC() & BYTE_MASK) == 0) {
        Script_Request(g_Task->direction);
        g_Game.current->u.field.mode.unsigned_value = 0;
        g_Task->header.mode                         = 1;
        ACTOR_CLEAR_STEP();
        g_Task->unk_03 = 0;
    }
}
