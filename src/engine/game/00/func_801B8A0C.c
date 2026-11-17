#include "game_00.h"

MATCH void func_801B8A0C(void) {
    Actor* work;

    g_Game.current->u.field.counter.value = 3;
    work                                  = g_Task;
    work->direction                       = work->param.unk_0B;
    Actor_RequestScript(g_Task->direction);
    g_Game.current->u.field.mode.value = 0;
    g_Task->header.mode                = 1;
    g_Task->header.step                = 0;
    g_Task->unk_03                     = 0;
}
