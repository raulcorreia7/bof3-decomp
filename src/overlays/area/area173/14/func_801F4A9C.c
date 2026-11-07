#include "area173_14.h"

MATCH void func_801F4A9C(void) {
    if (g_GameState->leader_id == CHAR_ID_GARR) {
        FIELD(u16, (u8*)g_ScriptState, 0xAu) += 1;
    }
}
