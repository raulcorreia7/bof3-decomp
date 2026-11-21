#include "engine/game/00/game_00.h"

MATCH void Game_UpdateScene(void) {
    SYS_DISPATCH_BYTE(g_SceneSteps, D_801448EA[0]);
}
