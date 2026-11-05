#include "game_00.h"

MATCH void func_801B8A0C(void) {
    Actor* work;

    g_GameState->counter_11C.s8_value = 3;
    work                              = g_Task;
    work->direction_08                = (u8)work->unk_0B;
    Actor_RequestScript(g_Task->direction_08);
    g_GameState->mode_12B.s8_value = 0;
    g_Task->mode                   = 1;
    g_Task->step                   = 0;
    g_Task->unk_03                 = 0;
}
