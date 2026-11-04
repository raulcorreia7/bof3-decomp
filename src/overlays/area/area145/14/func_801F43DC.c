#include "area145_14.h"

MATCH s32 func_801F43DC(s32 entry_x, s32 entry_y) {
    if ((D_80143F03 == 0) && (entry_y == 0x98000) && ((u32)((entry_x >> 0x10) - 0x1B) < 2U) &&
        ((u32)((u16)D_80145EC6 - 0x1B) < 2U)) {
        Game_SetScriptActive();
        D_801448EB = 0x14;
        D_801448EC = 0x19;
        return 1;
    }
    if (D_80143F03 == 4) {
        if ((SYS_TestFlag(g_SceneEventFlags, 0x2D) != 0) && ((u32)((entry_x >> 0x10) - 9) < 3U)) {
            if (((u32)((entry_y >> 0x10) - 0x62) < 3U) && ((D_80145E98 == 0) || ((u32)(D_80145E98 - 6) < 2U))) {
                *g_ScriptVars = 0;
                func_801BE1B0(3U);
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}
