#include "engine/slus/slus.h"

/* clears SCENE_STATE_SCRIPT_ACTIVE and bit 8 of g_Game.flags. */
MATCH void Game_ClearScriptActive(void) {
    u8* p = &g_SceneState.flags_01;
    *p &= ~SCENE_STATE_SCRIPT_ACTIVE;
    g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
}
