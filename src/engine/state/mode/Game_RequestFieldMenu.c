#include "engine/game/00/game_00.h"

/* func_801B5758 */
/* Opens the field menu on the menu button; true when requested. */
MATCH bool Game_RequestFieldMenu(void) {
    if (g_InputPressed & g_InputMasks[FIELD_INPUT_MENU]) {
        if (!(g_Game.flags & GAME_FLAG_MENU_LOCK)) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 5));
            g_Game.walk_flags |= AREA_WALK_MENU_ACTIVE;
            Actor_RequestRoute(g_Task->direction);
            g_Task->header.mode = FIELD_TASK_MODE_MENU;
            g_Task->header.step = 0;
            return 1;
        }
    }
    return 0;
}
