#include "game_00.h"

MATCH bool func_801B5910(void) {
    if (!(g_Game.flags & 0x2000)) {
        if (!(g_GameRequestFlags & (AREA_LOAD_FLAG_WORLD_MAP | AREA_LOAD_FLAG_FISHING | AREA_LOAD_FLAG_NO_ACTOR_SCRIPT | AREA_LOAD_FLAG_SHOP)) && (g_InputPressed & PADstart)) {
            func_801B5BDC(g_Task->direction_08);
            g_GameStateIndex    = GAME_REQUEST_SCENE_CAMERA;
            g_Task->header.mode = 0xE;
            g_Task->header.step = 0;
            return 1;
        }
        return 0;
    }
    return 0;
}
