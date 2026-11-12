#include "game_00.h"

MATCH void func_801C4D58(void) {
    Actor* work;
    Actor* state;
    Actor* reload;
    s32    doubled;

    g_Game.current->u.field.counter_11C.s8_value = (g_Task->state_70.word + 2);
    func_801C2538();
    work          = g_Task;
    doubled       = work->timer * 2;
    work->timer   = (doubled * (work->state_70.word + 1));
    state         = g_Task;
    work->vz      = 0;
    state->unk_0A = (state->timer >> 1);
    Actor_RequestScript((g_Task->direction_08 + 8) & BYTE_MASK);
    Actor_Move();
    reload        = g_Task;
    reload->timer = (reload->timer - 1);
}
