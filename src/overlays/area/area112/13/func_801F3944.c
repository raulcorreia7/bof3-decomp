#include "area112_13.h"

MATCH s32 func_801F3944(s32 entry_x, s32 entry_y) {
    if ((D_80143F03 == 3) && (SYS_TestFlag(g_SceneEventFlags, 51) != 0) && (SYS_TestFlag(g_SceneEventFlags - 0x38, 16) != 0) && (((entry_x >> 0x10) - 11) < 3U)) {
        if ((((entry_y >> 0x10) - 87) < 3U) && ((g_Game.members[0].facing == FACING_UP_LEFT) || ((g_Game.members[0].facing - 6) < 2U))) {
            *g_ScriptVars = 0;
            func_801BE1B0(0U);
            return 1;
        }
        return 0;
    }
    return 0;
}
