#include "area145_14.h"

MATCH s32 func_801F43DC(s32 entry_x, s32 entry_y) {
    if ((g_GameCellType == 0) && (entry_y == TO_COORD(9) + COORD_HALF) && (((entry_x >> 0x10) - 27) < 2U) && (((u16)g_Game.members[0].pos.x.part.integer - 0x1B) < 2U)) {
        Scene_StartEvent(0x14, 0x19);
        return 1;
    }
    if (g_GameCellType == 4) {
        if ((SYS_TestFlag(g_SceneEventFlags, 45) != 0) && (((entry_x >> 0x10) - 9) < 3U)) {
            if ((((entry_y >> 0x10) - 98) < 3U) && ((g_Game.members[0].facing == FACING_UP_LEFT) || ((g_Game.members[0].facing - 6) < 2U))) {
                *g_ScriptVars = 0;
                Scene_SetupParty(3U);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
