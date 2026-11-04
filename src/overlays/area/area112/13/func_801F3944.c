#include "area112_13.h"

MATCH s32 func_801F3944(s32 arg0, s32 arg1) {
    if ((D_80143F03 == 3) && (SYS_TestFlag(g_SceneEventFlags, 0x33) != 0) &&
        (SYS_TestFlag(g_SceneEventFlags - 0x38, 0x10) != 0) && ((u32)((arg0 >> 0x10) - 0xB) < 3U)) {
        if (((u32)((arg1 >> 0x10) - 0x57) < 3U) && ((D_80145E98 == 0) || ((u32)(D_80145E98 - 6) < 2U))) {
            *g_ScriptVars = 0;
            func_801BE1B0(0U);
            return 1;
        }
        /* Duplicate return node #9. Try simplifying control flow for better match */
        return 0;
    }
    return 0;
}
