#include "game_00.h"

MATCH s32 func_801B5884(void) {
    if (!(g_GameFlags & 0x2000) && (D_8014625C & g_InputMasks[INPUT_SLOT_LOOK])) {
        g_GameStateIndex = GAME_REQUEST_CAMERA_LOOK;
        func_801B5BDC(g_Task->direction_08);
        g_Task->header.mode = 1;
        ACTOR_CLEAR_STEP();
        return 1;
    }
    return 0;
}
