#include "engine/game/00/game_00.h"

/* func_801B1AE8 */
MATCH void Game_LeaderSwitchRun(void) {
    g_GameLeaderSwitchSteps[SELF(Actor)->header.step]();
}
