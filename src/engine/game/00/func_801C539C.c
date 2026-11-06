#include "game_00.h"

MATCH bool func_801C539C(void) {
    Actor* work;
    Actor* state;
    Actor* reload;
    s32    doubled;

    if (!(func_8014DAEC() & BYTE_MASK)) {
        return false;
    }
    g_GameState->counter_11C.s8_value = (FIELD(s32, g_Task, 0x70u) + 2);
    func_801C2538();
    work          = g_Task;
    doubled       = work->unk_09 * 2;
    work->unk_09  = (doubled * (FIELD(s32, work, 0x70u) + 1));
    state         = g_Task;
    work->vz      = 0;
    state->unk_0A = (state->unk_09 >> 1);
    Actor_RequestScript((g_Task->direction_08 + 8) & BYTE_MASK);
    func_801C57B4();
    reload         = g_Task;
    reload->unk_09 = (reload->unk_09 - 1);
    return true;
}
