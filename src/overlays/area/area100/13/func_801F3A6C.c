#include "area100_13.h"

MATCH s32 func_801F3A6C(s32 arg0, s32 arg1) {
    if (D_80143F03 == 3 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((arg0 >> 16) - 0x45) < 3) {
        if ((u32)((arg1 >> 16) - 0x33) < 3 && (g_BattlePartyBattlers[0].facing == 0 || (u32)(g_BattlePartyBattlers[0].facing - 6) < 2)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
