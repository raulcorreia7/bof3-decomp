#include "area008_13.h"

MATCH void func_801F37BC(void) {
    Actor* s;
    Actor* e;
    u8     index;

    s     = SELF(Actor);
    index = s->param.unk_0B;
    e     = &g_Actors[index];
    SELF_SET(e);
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->header.mode = 0x0E;
    } else if ((e->script_pc == 8) && (e->unk_4A == 1)) {
        Script_Select(4);
        s->header.mode = 0x0B;
    }
    g_Self = s;
}
