#include "area142_13.h"

MATCH void func_801F3458(void) {
    if (g_ScriptVars[0] != 1) {
        if (g_GameStateIndex == 3) {
            g_SpadWork->flags_00 |= 0x40;
            g_SpadWork->unk_04 = 1;
        }
        g_ScriptState->cursor -= 2;
    }
}
