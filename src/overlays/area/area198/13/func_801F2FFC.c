#include "area198_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FFC(void) {
    Actor* work;

    u8  count;
    u16 position;

    work = g_Task;
    LOHU(work->pos.z.part.integer) -= 0x10;
    count = g_ScriptState->count_02;
    if (count < 0x80 && (count & 3) == 0) {
        position = work->script_pc - 2;
        Actor_BeginScript(D_801F43AC[(count >> 2) & 3], position);
    }
    g_ScriptState->count_02 += 1;

    if (g_Task->pos.z.part.integer < -0x280) {
        if (g_Task->tint.signed_bytes.delta.red >= -0x7F) {
            g_Task->tint.signed_bytes.delta.red -= 1;
        }
        if (g_Task->tint.signed_bytes.delta.green >= -0x7F) {
            g_Task->tint.signed_bytes.delta.green -= 1;
        }
        if (g_Task->tint.signed_bytes.delta.blue >= -0x7F) {
            g_Task->tint.signed_bytes.delta.blue -= 1;
        }
    }
    if (g_Task->pos.z.part.integer == -0xA00) {
        g_ScriptVars[0] += 1;
    }
    if (g_Task->pos.z.part.integer >= -0xC7F) {
        g_ScriptState->cursor -= 2;
    } else {
        g_ScriptState->count_02 = 0;
    }
}
#else
INCLUDE_ASM(func_801F2FFC);
#endif
