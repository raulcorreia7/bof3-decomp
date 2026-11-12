#include "game_00.h"

MATCH void func_801B315C(void) {
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        if (g_GameRequestFlags & 0x1) {
            func_801B5BDC(g_Task->direction_08);
        } else {
            Actor_RequestScript(g_Task->direction_08);
        }
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
