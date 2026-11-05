#include "area174_13.h"

MATCH void func_801F3D40(void) {
    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_ScriptState->cursor = (g_ScriptState->cursor - 2u);
    }
}
