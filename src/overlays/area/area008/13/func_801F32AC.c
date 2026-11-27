#include "area008_13.h"

MATCH void func_801F32AC(void) {
    Actor* e;
    u8     index;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        SELF(Actor)->header.mode = 0x0E;
        return;
    }
    if (g_ScriptVars[2] == 1) {
        index = SELF(Actor)->param.unk_0B;
        e     = &g_Actors[index];
        e->header.flags &= ~ACTOR_FLAG_HIDDEN;
        SELF(Actor)->header.mode = 2;
    }
}
