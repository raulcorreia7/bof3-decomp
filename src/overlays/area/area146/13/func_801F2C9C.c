#include "area146_13.h"

/* Script condition: D_80143F03 is 1, scene flag 0x33 is set, the high halves of
 * x and y fall in 0x44..0x46 and 0x2A..0x2C and g_Game.members[0].facing is 0, 6 or 7; the
 * match clears the first script variable and calls func_801BE1B0(0). */
MATCH s32 func_801F2C9C(s32 x, s32 y) {
    if (D_80143F03 == 1 && SYS_TestFlag(g_SceneEventFlags, 51) != 0 && ((x >> 16) - 68) < 3U) {
        if (((y >> 16) - 42) < 3U && (g_Game.members[0].facing == FACING_UP_LEFT || (g_Game.members[0].facing - 6) < 2U)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
