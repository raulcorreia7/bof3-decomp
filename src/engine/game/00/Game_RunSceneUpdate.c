#include "game_00.h"

MATCH void Game_RunSceneUpdate(void) {
    SYS_DISPATCH_BYTE(g_SceneStates, D_801448EA[0]);
}
