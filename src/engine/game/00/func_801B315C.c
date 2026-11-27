#include "game_00.h"

MATCH void func_801B315C(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
            Actor_RequestRoute(SELF(Actor)->direction);
        } else {
            Script_Request(SELF(Actor)->direction);
        }
        SELF(Actor)->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
