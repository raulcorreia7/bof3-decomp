#include "area142_13.h"

MATCH void func_801F34D0(void) {
    if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
        g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
        Actor_SelectScript(g_Task->direction_08);
        g_Task->unk_04 = 0;
    }
    g_ScriptState->cursor -= 2;
}
