#include "area103_13.h"

MATCH void func_801F5778(void) {
    if (g_GameState->chr.character_id == CHAR_ID_RYU_YOUNG) {
        u8* script_vars = &g_ScriptVars[0];

        script_vars[0] += 1;
    }
}
