#include "game_00.h"

MATCH void func_801B781C(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0 && (func_801C2AAC() & BYTE_MASK) == 0) {
        Actor_RequestScript(g_Task->direction_08);
        g_Game.current->u.field.mode_12B.u8_value = 0;
        g_Task->header.mode                       = 1;
        ACTOR_CLEAR_STEP();
        g_Task->unk_03 = 0;
    }
}
