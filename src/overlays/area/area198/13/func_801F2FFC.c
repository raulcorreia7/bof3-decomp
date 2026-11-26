#include "area198_13.h"

MATCH void func_801F2FFC(void) {
    Actor* work;
    u8     count;
    s8     tint_a;
    s8     tint_b;
    s8     tint_c;

    work = SELF(Actor);
    COORD_INT(work->pos.z) -= 0x10;
    count = g_ScriptState->count;
    if (count < 0x80 && (count & 3) == 0) {
        Script_Begin(D_801F43AC[(count >> 2) & 3], (u16)(work->script_pc - 2));
    }
    g_ScriptState->count++;
    work = SELF(Actor);
    if (COORD_INT(work->pos.z) < -0x280) {
        tint_a = work->tint.steps.delta.r;
        if (tint_a >= -0x7F) {
            work->tint.steps.delta.r = tint_a - 1;
            work                     = SELF(Actor);
        }
        tint_b = work->tint.steps.delta.g;
        if (tint_b >= -0x7F) {
            work->tint.steps.delta.g = tint_b - 1;
        }
        work   = SELF(Actor);
        tint_c = work->tint.steps.delta.b;
        if (tint_c >= -0x7F) {
            work->tint.steps.delta.b = tint_c - 1;
        }
    }
    if (COORD_INT(SELF(Actor)->pos.z) == -0xA00) {
        g_ScriptVars[0]++;
    }
    if (COORD_INT(SELF(Actor)->pos.z) >= -0xC7F) {
        g_ScriptState->cursor -= 2;
    } else {
        g_ScriptState->count = 0;
    }
}
