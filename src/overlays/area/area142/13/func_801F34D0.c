#include "area142_13.h"

MATCH void func_801F34D0(void) {
    if (g_GameStateIndex != GAME_REQUEST_BATTLE) {
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_HIDDEN;
        Script_Select(SELF(Actor)->direction);
        SELF(Actor)->unk_04 = 0;
    }
    g_ScriptState->cursor -= 2;
}
