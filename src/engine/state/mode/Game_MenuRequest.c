#include "engine/game/00/game_00.h"

/* func_801B2A00 */
MATCH void Game_MenuRequest(void) {
    SELF(Actor)->header.step = 1;
    g_GameStateIndex         = GAME_REQUEST_MENU;
}
