#include "game_00.h"

MATCH void func_801B8A0C(void) {
    Actor* work;

    g_Game.current->u.field.counter_11C.s8_value = 3;
    work                                         = g_Task;
    work->direction_08                           = work->param.unk_0B;
    Actor_RequestScript(g_Task->direction_08);
    g_Game.current->u.field.mode_12B.s8_value = 0;
    g_Task->header.mode                       = 1;
    g_Task->header.step                       = 0;
    g_Task->unk_03                            = 0;
}
