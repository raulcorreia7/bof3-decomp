#include "game_00.h"

MATCH void func_8019E2A8(void) {
    Actor* work;
    Actor* state;
    Actor* other;
    Actor* flags;

    Area_SelectSceneRecord(0x18);
    g_Task->active_flags             = 0;
    g_Task->unk_2A                   = 0;
    work                             = g_Task;
    work->unk_2B                     = (work->unk_2B + 1);
    g_Task->unk_48                   = 0;
    state                            = g_Task;
    state->tint.signed_bytes.unk_5D  = 0;
    other                            = g_Task;
    state->vz                        = 64;
    state->gravity                   = -8;
    other->tint.signed_bytes.unk_5E  = 0;
    g_Task->tint.signed_bytes.unk_5F = 0;
    Actor_SelectScript(8);
    flags              = g_Task;
    flags->header.step = (flags->header.step + 1);
}
