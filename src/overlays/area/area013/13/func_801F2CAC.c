#include "area013_13.h"

MATCH void func_801F2CAC(void) {
    if (g_GameState->chr.character_id != CHAR_ID_NINA_ADULT) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 0xC);
    }
}
