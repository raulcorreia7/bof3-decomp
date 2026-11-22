#include "game_00.h"

MATCH void func_8019E2A8(void) {
    Actor* work;
    Actor* state;
    Actor* other;
    Actor* flags;

    Area_SceneSelectRecord(0x18);
    g_Task->active_flags       = 0;
    g_Task->mirror             = 0;
    work                       = g_Task;
    work->unk_2B               = (work->unk_2B + 1);
    g_Task->unk_48             = 0;
    state                      = g_Task;
    state->tint.steps.delta.r  = 0;
    other                      = g_Task;
    state->vz                  = 64;
    state->gravity             = -8;
    other->tint.steps.delta.g  = 0;
    g_Task->tint.steps.delta.b = 0;
    Script_Select(8);
    flags              = g_Task;
    flags->header.step = (flags->header.step + 1);
}
