#include "game_00.h"

MATCH void func_801C4D58(void) {
    Actor* work;
    Actor* state;
    Actor* reload;
    s32    doubled;

    g_GameState->u.field.counter_11C.s8_value = (FIELD(s32, g_Task, 0x70u) + 2);
    func_801C2538();
    work          = g_Task;
    doubled       = work->timer * 2;
    work->timer   = (doubled * (FIELD(s32, work, 0x70u) + 1));
    state         = g_Task;
    work->vz      = 0;
    state->unk_0A = (state->timer >> 1);
    Actor_RequestScript((g_Task->direction_08 + 8) & BYTE_MASK);
    func_801C57B4();
    reload        = g_Task;
    reload->timer = (reload->timer - 1);
}
