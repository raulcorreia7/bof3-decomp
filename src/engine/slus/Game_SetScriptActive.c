#include "engine/slus/slus.h"

/* Sets SCENE_STATE_SCRIPT_ACTIVE and bit 8 of g_Game.flags. Declared int with no value returned: callers
 * keep v0 for the unused result, so their constants after the call land in v1 (scena03 func_801FC6C4). */
MATCH s32 Game_SetScriptActive(void) {
    u8* p = &g_SceneState.flags_01;
    (*p) |= SCENE_STATE_SCRIPT_ACTIVE;
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
}
