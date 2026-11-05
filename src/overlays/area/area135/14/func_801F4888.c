#include "area135_14.h"

MATCH void func_801F4888(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        func_801F5F28();
    } else {
        g_ScriptState->cursor = (g_ScriptState->cursor - 2);
    }
}
