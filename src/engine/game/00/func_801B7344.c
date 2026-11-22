#include "game_00.h"

MATCH void func_801B7344(void) {
    if (func_801C27E0(8) & BYTE_MASK) {
        g_Game.current->u.field.mode.unsigned_value = 0;
        TASK(Actor)->header.mode                    = 1;
        ACTOR_CLEAR_STEP();
        TASK(Actor)->unk_03 = 0;
    }
}
