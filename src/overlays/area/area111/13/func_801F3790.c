#include "area111_13.h"

MATCH void func_801F3790(void) {
    u32 slot = -(((s32)g_CurrentActor - (s32)g_PartyActors) * 0xD79435E5) >> 3;

    if (g_ScriptVars[3] != (16 << slot)) {
        g_ScriptState->cursor -= 2;
    }
}
