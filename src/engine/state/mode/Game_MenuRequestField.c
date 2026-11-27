#include "engine/game/00/game_00.h"

/* func_801B5758 */
/* Opens the field menu on the menu button; true when requested. */
MATCH bool Game_MenuRequestField(void) {
    if (g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_MENU]) {
        if (!(g_Game.flags & GAME_FLAG_MENU_LOCK)) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
            g_Game.walk_flags |= AREA_WALK_MENU_ACTIVE;
            Actor_RequestRoute(SELF(Actor)->direction);
            SELF(Actor)->header.mode = FIELD_TASK_MODE_MENU;
            SELF(Actor)->header.step = 0;
            return 1;
        }
    }
    return 0;
}
