#include "game_00.h"

MATCH void func_801B315C(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
            Actor_RequestRoute(g_Task->direction);
        } else {
            Actor_RequestScript(g_Task->direction);
        }
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
