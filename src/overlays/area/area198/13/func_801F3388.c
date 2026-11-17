#include "area198_13.h"

MATCH void func_801F3388(void) {
    Actor* work;
    Actor* task;

    work = g_Task;
    work->pos.x.fixed += D_801F43B0[work->unk_0A & 0xF] << 11;
    work->pos.y.fixed -= D_801F43B0[work->unk_0A & 0xF] << 11;
    work->pos.z.part.integer += D_801F43B0[work->unk_0A & 0xF] * 16;
    work->unk_0A -= 1;
    g_ScriptState->cursor -= 2;

    if (g_ScriptVars[1] != 0) {
        s32 index;

        index = func_8019601C() & BYTE_MASK;
        if (index != GAME_NONE) {
            g_SpawnedActors[index].header.flags = ACTOR_FLAG_IN_USE;
            g_SpawnedActors[index].type         = 0xAC;
        }
        g_ScriptVars[1]                 = 0;
        task                            = g_Task;
        task->tint.signed_bytes.delta.b = -0x40;
        task->tint.signed_bytes.delta.g = -0x40;
        task->tint.signed_bytes.delta.r = -0x40;
    } else {
        if (g_Task->tint.signed_bytes.delta.r != 0) {
            g_Task->tint.signed_bytes.delta.r += 8;
        }
        if (g_Task->tint.signed_bytes.delta.g != 0) {
            g_Task->tint.signed_bytes.delta.g += 8;
        }
        if (g_Task->tint.signed_bytes.delta.b != 0) {
            g_Task->tint.signed_bytes.delta.b += 8;
        }
    }
}
