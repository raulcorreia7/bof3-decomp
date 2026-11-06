#include "game_00.h"

MATCH s32 func_801B5910(void) {
    if (!(g_GameFlags & 0x2000)) {
        if (!(g_GameRequestFlags & 0x69) && (g_InputPressed & PADstart)) {
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
