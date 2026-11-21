#include "engine/game/00/game_00.h"

/* func_80198B00 */
MATCH void Game_RunScene(void) {
    Area_DispatchScene();
    Game_RunSceneFrame();
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        g_GameEntryState = GAME_MODE_FIELD;
    }
}
