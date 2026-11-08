#include "area034_13.h"

MATCH void func_801F2CDC(void) {
    if (g_Game.current->chr.character_id != CHAR_ID_RYU_ADULT) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 0x15);
    }
}
