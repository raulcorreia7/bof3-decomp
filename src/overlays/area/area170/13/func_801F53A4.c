#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F53A4(s32 x, s32 y) {
    if (g_GameCellType == 4) {
        if (((y == 0x708000 || y == 0x738000) && (u32)((x >> 16) - 3) < 3U) || (x == 0x28000 && (u32)((y >> 16) - 0x71) < 3U) || (x == 0x58000 && (u32)((y >> 16) - 0x71) < 3U)) {
            Game_SetScriptActive();
            g_SceneEventMode = 0x25;
            g_SceneEventStep = 0;
            return 1;
        }
    }
    if (g_GameCellType != 5) {
        return 0;
    }
    if (((y == 0x8E8000 || y == 0x918000) && (u32)((x >> 16) - 9) < 3U) || (x == 0x88000 && (u32)((y >> 16) - 0x8F) < 3U) || (x == 0xB8000 && (u32)((y >> 16) - 0x8F) < 3U)) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x25;
        g_SceneEventStep = 0xA;
        return 1;
    }
    if (((y == 0x8E8000 || y == 0x918000) && (u32)((x >> 16) - 0x10) < 3U) || (x == 0xF8000 && (u32)((y >> 16) - 0x8F) < 3U) || (x == 0x128000 && (u32)((y >> 16) - 0x8F) < 3U)) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x25;
        g_SceneEventStep = 0x14;
        SYS_SetFlag(g_SceneEventFlags, 0x7E);
        g_Game.flags &= 0xEFEF;
        return 1;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 0x7E) != 0) {
        return 0;
    }
    if (x == 0x208000 && y == 0x900000 && g_Game.members[0].facing == FACING_LEFT) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x25;
        g_SceneEventStep = 0x32;
        return 1;
    }
    if (x == 0x218000 && y == 0x900000 && g_Game.members[0].facing == FACING_RIGHT) {
        g_SceneEventMode = 0x25;
        g_SceneEventStep = 0x3C;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F53A4);
#endif
