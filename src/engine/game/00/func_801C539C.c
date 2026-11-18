#include "game_00.h"

MATCH bool func_801C539C(void) {
    Actor* work;
    Actor* state;
    Actor* reload;
    s32    doubled;

    if (!(Actor_StepAnimOnce() & BYTE_MASK)) {
        return false;
    }
    g_Game.current->u.field.counter.value = (g_Task->voice_flags.raw + 2);
    Area_SetWalkVelocity();
    work          = g_Task;
    doubled       = work->timer * 2;
    work->timer   = (doubled * (work->voice_flags.raw + 1));
    state         = g_Task;
    work->vz      = 0;
    state->unk_0A = (state->timer >> 1);
    Actor_RequestScript((g_Task->direction + 8) & BYTE_MASK);
    Actor_Move();
    reload        = g_Task;
    reload->timer = (reload->timer - 1);
    return true;
}
