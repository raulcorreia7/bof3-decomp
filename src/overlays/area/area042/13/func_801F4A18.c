#include "area042_13.h"

MATCH s32 func_801F4A18(s32 entry_x, s32 entry_y) {
    if (((entry_y == TO_COORD(48) + COORD_HALF) && (((entry_x >> 0x10) - 123) < 2U)) || ((entry_y == TO_COORD(54) + COORD_HALF) && (((entry_x >> 0x10) - 29) < 3U))) {
        SYS_ClearFlag(g_SceneEventFlags, 0x11U);
        SYS_ClearFlag(g_SceneEventFlags, 0xBU);
        SYS_ClearFlag(g_SceneEventFlags, 0x12U);
        SYS_ClearFlag(g_SceneEventFlags, 0x13U);
        SYS_ClearFlag(g_SceneEventFlags, 0x14U);
        SYS_ClearFlag(g_SceneEventFlags, 0x15U);
        g_GameFlags &= 0xFFDF;
        if (g_SceneEventMode == 7) {
            g_SceneEventMode = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            D_801448EE       = 0;
        }
    }
    return 0;
}
