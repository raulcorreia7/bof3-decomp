#include "game_00.h"

MATCH void func_801B2A20(void) {
    if (g_GameStateIndex != GAME_REQUEST_MENU) {
        g_AreaWalkFlags &= ~AREA_WALK_RUN_ACTIVE;
        g_Task->mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
