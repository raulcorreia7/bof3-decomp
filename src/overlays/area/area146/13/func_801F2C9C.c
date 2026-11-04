#include "area146_13.h"

/* Script condition: D_80143F03 is 1, scene flag 0x33 is set, the high halves of
 * x and y fall in 0x44..0x46 and 0x2A..0x2C and D_80145E98 is 0, 6 or 7; the
 * match clears the first script variable and calls func_801BE1B0(0). */
MATCH s32 func_801F2C9C(s32 x, s32 y) {
    if (D_80143F03 == 1 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((x >> 16) - 0x44) < 3U) {
        if ((u32)((y >> 16) - 0x2A) < 3U && (D_80145E98 == 0 || (u32)(D_80145E98 - 6) < 2U)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
