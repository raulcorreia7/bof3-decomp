#include "area142_13.h"

MATCH void func_801F34D0(void) {
    if (g_GameStateIndex != 3) {
        g_SpadWork->flags_00 &= 0xBF;
        Actor_SelectScript(g_SpadWork->direction_08);
        g_SpadWork->unk_04 = 0;
    }
    g_ScriptState->cursor -= 2;
}
