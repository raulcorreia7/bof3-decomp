#include "game_00.h"

MATCH s32 func_801B5758(void) {
    if (g_InputPressed & g_InputMasks[INPUT_SLOT_MENU]) {
        if (!(g_GameFlags & GAME_FLAG_RUN_LOCK)) {
            SND_PlayCue(EMI_CUE_ID(1, 5));
            g_AreaWalkFlags |= AREA_WALK_RUN_ACTIVE;
            func_801B5BDC(g_Task->direction_08);
            g_Task->header.mode = 4;
            g_Task->header.step = 0;
            return 1;
        }
    }
    return 0;
}
