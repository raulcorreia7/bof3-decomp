#include "area042_13.h"

MATCH s32 func_801F4A18(s32 entry_x, s32 entry_y) {
    if (((entry_y == 0x308000) && ((u32)((entry_x >> 0x10) - 0x7B) < 2U)) ||
        ((entry_y == 0x368000) && ((u32)((entry_x >> 0x10) - 0x1D) < 3U))) {
        SYS_ClearFlag(g_SceneEventFlags, 0x11U);
        SYS_ClearFlag(g_SceneEventFlags, 0xBU);
        SYS_ClearFlag(g_SceneEventFlags, 0x12U);
        SYS_ClearFlag(g_SceneEventFlags, 0x13U);
        SYS_ClearFlag(g_SceneEventFlags, 0x14U);
        SYS_ClearFlag(g_SceneEventFlags, 0x15U);
        g_GameFlags &= 0xFFDF;
        if (D_801448EB == 7) {
            D_801448EB = 0;
            D_801448EC = 0;
            D_801448EE = 0;
        }
    }
    return 0;
}
