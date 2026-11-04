#include "area008_13.h"

MATCH void func_801F34FC(void) {
    Actor* s;
    Actor* e;
    u8     idx;

    s          = g_SpadWork;
    idx        = s->unk_0B;
    e          = &g_Actors[idx];
    g_SpadWork = (Actor*)e;
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->unk_01 = 0x0E;
    } else if ((e->script_pc == 2) && (e->unk_4A == 1)) {
        s->unk_01 = 5;
    }
    g_SpadWork = s;
}
