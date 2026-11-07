#include "area018_13.h"

MATCH void func_801F2C68(void) {
    if (g_GameState->leader_id != CHAR_ID_GARR) {
        g_ScriptState->cursor = (g_ScriptState->cursor + 9);
    }
}
