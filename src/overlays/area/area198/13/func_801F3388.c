#include "area198_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3388(void) {
    Actor* work;
    Actor* cell;
    u8     slot;
    s32    step;

    work = g_Task;
    work->pos.x.fixed += D_801F43B0[work->unk_0A & 0xF] << 11;
    work->pos.y.fixed -= D_801F43B0[work->unk_0A & 0xF] << 11;
    step = D_801F43B0[work->unk_0A & 0xF] << 4;
    work->unk_0A -= 1;
    LOHU(work->pos.z.part.integer) += step;
    g_ScriptState->cursor -= 2;

    if (g_ScriptVars[1] != 0) {
        slot = func_8019601C();
        if (slot != 0xFF) {
            g_SpawnedActors[slot].header.flags = 1;
            g_SpawnedActors[slot].type         = 0xAC;
        }
        g_ScriptVars[1]                     = 0;
        cell                                = g_Task;
        cell->tint.signed_bytes.delta.blue  = -0x40;
        cell->tint.signed_bytes.delta.green = -0x40;
        cell->tint.signed_bytes.delta.red   = -0x40;
    } else {
        if (g_Task->tint.signed_bytes.delta.red != 0) {
            g_Task->tint.signed_bytes.delta.red += 8;
        }
        if (g_Task->tint.signed_bytes.delta.green != 0) {
            g_Task->tint.signed_bytes.delta.green += 8;
        }
        if (g_Task->tint.signed_bytes.delta.blue != 0) {
            g_Task->tint.signed_bytes.delta.blue += 8;
        }
    }
}
#else
INCLUDE_ASM(func_801F3388);
#endif
