#include "area075_13.h"

MATCH void func_801F3680(void) {
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        g_SpadWork->y.fixed = g_AreaScrollTargetY;
        g_ScriptState->cursor -= 2;
    } else {
        g_SpadWork->unk_04 = 0;
    }
}
