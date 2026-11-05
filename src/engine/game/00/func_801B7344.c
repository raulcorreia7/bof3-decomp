#include "game_00.h"

MATCH void func_801B7344(void) {
    if (func_801C27E0(8) & BYTE_MASK) {
        g_GameState->mode_12B.u8_value = 0;
        g_Task->mode                   = 1;
        ACTOR_CLEAR_STATE();
        g_Task->unk_03 = 0;
    }
}
