#include "area143_13.h"

/* Script condition: D_80143F03 is 1, the high halves of x and y fall in
 * 0x37..0x39 and 0x64..0x66, and g_BattlePartyBattlers[0].facing is 0, 6 or 7; the match clears the
 * first script variable and calls func_801BE1B0(0). */
MATCH s32 func_801F3D78(s32 x, s32 y) {
    if (D_80143F03 == 1 && ((x >> 16) - 55) < 3U) {
        if (((y >> 16) - 100) < 3U &&
            (g_BattlePartyBattlers[0].facing == FACING_UP_LEFT || (g_BattlePartyBattlers[0].facing - 6) < 2U)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
