#include "engine/slus/slus.h"

/* Sets SCENE_STATE_SCRIPT_ACTIVE and bit 8 of g_Game.flags. */
MATCH s32 Game_SetScriptActive(void) {
    u8* p = &g_SceneState.flags_01;
    (*p) |= SCENE_STATE_SCRIPT_ACTIVE;
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
}
