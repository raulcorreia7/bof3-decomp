#include "area042_13.h"

MATCH s32 func_801F4A18(s32 entry_x, s32 entry_y) {
    if (((entry_y == 0x308000) && (((entry_x >> 0x10) - 0x7B) < 2U)) ||
        ((entry_y == 0x368000) && (((entry_x >> 0x10) - 0x1D) < 3U))) {
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x11U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0xBU);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x12U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x13U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x14U);
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x15U);
        g_GameFlags &= 0xFFDF;
        if (g_SaveData.scene_event.mode == 7) {
            g_SaveData.scene_event.mode = 0;
            g_SaveData.scene_event.step = 0;
            D_801448EE                  = 0;
        }
    }
    return 0;
}
