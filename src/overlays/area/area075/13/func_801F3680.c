#include "area075_13.h"

MATCH void func_801F3680(void) {
    if (g_GameStateIndex != GAME_REQUEST_IDLE) {
        TASK(Actor)->pos.y.fixed = g_AreaScrollTargetY;
        g_ScriptState->cursor -= 2;
    } else {
        TASK(Actor)->unk_04 = 0;
    }
}
