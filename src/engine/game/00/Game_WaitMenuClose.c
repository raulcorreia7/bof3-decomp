#include "game_00.h"

/* func_801B2A20 */
MATCH void Game_WaitMenuClose(void) {
    if (g_GameStateIndex != GAME_REQUEST_MENU) {
        g_AreaWalkFlags &= ~AREA_WALK_MENU_ACTIVE;
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
    }
}
