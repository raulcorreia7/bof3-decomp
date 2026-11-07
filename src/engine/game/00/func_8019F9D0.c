#include "game_00.h"

MATCH void func_8019F9D0(void) {
    g_Task->header.mode = g_Task->param.unk_0B;
    ACTOR_CLEAR_STEP();
    g_Task->unk_03 = 0;
    g_Task->unk_04 = 0;
    g_Task->unk_09 = 0;
}
