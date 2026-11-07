#include "game_00.h"

MATCH s32 func_801B5758(void) {
    if (g_InputPressed & g_InputMasks[FIELD_INPUT_MENU]) {
        if (!(g_GameFlags & GAME_FLAG_MENU_LOCK)) {
            SND_PlayCue(EMI_CUE_ID(1, 5));
            g_AreaWalkFlags |= AREA_WALK_MENU_ACTIVE;
            func_801B5BDC(g_Task->direction_08);
            g_Task->header.mode = FIELD_TASK_MODE_MENU;
            g_Task->header.step = 0;
            return 1;
        }
    }
    return 0;
}
