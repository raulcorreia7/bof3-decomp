#include "area008_13.h"

MATCH void func_801F32AC(void) {
    Actor* e;
    u8     idx;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        ((u8*)g_SpadWork)[1] = 0x0E;
        return;
    }
    if (g_ScriptVars[2] == 1) {
        idx = g_SpadWork->unk_0B;
        e   = &g_Actors[idx];
        e->flags_00 &= ~ACTOR_FLAG_HIDDEN;
        ((u8*)g_SpadWork)[1] = 2;
    }
}
