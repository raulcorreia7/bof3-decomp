#include "area100_13.h"

MATCH s32 func_801F3A6C(s32 x, s32 y) {
    if (D_80143F03 == 3 && SYS_TestFlag(g_SceneEventFlags, 51) != 0 && (u32)((x >> 16) - 69) < 3) {
        if ((u32)((y >> 16) - 51) < 3 && (g_Game.members[0].facing == FACING_UP_LEFT || (u32)(g_Game.members[0].facing - 6) < 2)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
