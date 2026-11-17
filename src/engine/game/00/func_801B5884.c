#include "game_00.h"

MATCH bool func_801B5884(void) {
    if (!(g_Game.flags & 0x2000) && (g_Game.input & g_InputMasks[FIELD_INPUT_VIEW])) {
        g_GameStateIndex = GAME_REQUEST_CAMERA_LOOK;
        Actor_RequestRoute(g_Task->direction);
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
