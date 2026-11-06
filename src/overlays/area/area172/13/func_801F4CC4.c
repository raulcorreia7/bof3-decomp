#include "area172_13.h"

/* Script condition: with D_80143F03 clear, x is exactly 0x248000, y falls in the
 * 0x35..0x37 block and g_BattlePartyBattlers[0].facing is 0, 6 or 7; the match starts the script and
 * queues g_SceneEventMode = 0x23. */
MATCH s32 func_801F4CC4(s32 x, s32 y) {
    if (D_80143F03 == 0) {
        if (x == 0x248000 && ((y >> 16) - 0x35) < 3U &&
            ((g_BattlePartyBattlers[0].facing - 6) < 2U || g_BattlePartyBattlers[0].facing == FACING_UP_LEFT)) {
            Game_SetScriptActive();
            g_SceneEventMode = 0x23;
            g_SceneEventStep = 0;
            return 1;
        }
    }
    return 0;
}
