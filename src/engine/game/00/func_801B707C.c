#include "game_00.h"

MATCH void func_801B707C(void) {
    if (func_801C27E0(4) & 0xFF) {
        g_GameState->flags_118 &= 0xFB;
        g_Task->unk_03 = 1;
    }
}
