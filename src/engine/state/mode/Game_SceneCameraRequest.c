#include "engine/game/00/game_00.h"

/* func_801B5910 */
/* Starts the scene camera state unless the area load flags forbid it; true when requested. */
MATCH bool Game_SceneCameraRequest(void) {
    if (!(g_Game.flags & 0x2000)) {
        if (!(g_GameRequestFlags & (AREA_LOAD_FLAG_WORLD_MAP | AREA_LOAD_FLAG_FISHING | AREA_LOAD_FLAG_NO_ACTOR_SCRIPT | AREA_LOAD_FLAG_SHOP)) && (g_PadStates[0].pressed & PADstart)) {
            Actor_RequestRoute(SELF(Actor)->direction);
            g_GameStateIndex         = GAME_REQUEST_SCENE_CAMERA;
            SELF(Actor)->header.mode = 0xE;
            SELF(Actor)->header.step = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
