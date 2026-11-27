#include "area008_13.h"

MATCH void func_801F3344(void) {
    Actor* s;
    Actor* e;
    u8     index;

    s     = SELF(Actor);
    index = s->param.unk_0B;
    e     = &g_Actors[index];
    SELF_SET(e);
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->header.mode = 0x0E;
    } else if (g_ScriptVars[2] == 2) {
        Script_Select(3);
        s->header.mode = 3;
    } else if (g_ScriptVars[2] == 5) {
        Script_Select(3);
        s->header.mode = 0x0A;
    }
    g_Self = s;
}
