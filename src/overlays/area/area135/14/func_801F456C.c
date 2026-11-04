#include "area135_14.h"

MATCH void func_801F456C(void) {
    if (g_SpadWork->y.part.integer >= 7 && (g_InputHeld & PADRdown)) {
        g_SpadWork->direction_08 = 1;
        g_ScriptState->unk_07    = 2;
        func_801ABBA8(g_ScriptState, g_SpadWork->direction_08);
        g_SpadWork->vz = 0;
        g_ScriptState->cursor -= 2;
    }
}
