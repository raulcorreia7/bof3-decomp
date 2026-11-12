#include "area042_13.h"

MATCH s32 func_801F4A18(s32 entry_x, s32 entry_y) {
    if (((entry_y == TO_COORD(48) + COORD_HALF) && (((entry_x >> 0x10) - 123) < 2U)) || ((entry_y == TO_COORD(54) + COORD_HALF) && (((entry_x >> 0x10) - 29) < 3U))) {
        SYS_ClearFlag(g_SceneEventFlags, 17U);
        SYS_ClearFlag(g_SceneEventFlags, 11U);
        SYS_ClearFlag(g_SceneEventFlags, 18U);
        SYS_ClearFlag(g_SceneEventFlags, 19U);
        SYS_ClearFlag(g_SceneEventFlags, 20U);
        SYS_ClearFlag(g_SceneEventFlags, 21U);
        g_GameFlags &= 0xFFDF;
        if (g_SceneEventMode == 7) {
            g_SceneEventMode = SCENE_EVENT_NONE;
            g_SceneEventStep = 0;
            D_801448EE       = 0;
        }
    }
    return 0;
}
