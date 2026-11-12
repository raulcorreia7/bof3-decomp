#include "area140_13.h"

MATCH s32 func_801F42F4(s32 entry_x, s32 entry_y) {
    if (D_80143F03 == 0 && SYS_TestFlag(g_SceneEventFlags, 102)) {
        if (entry_x != TO_COORD(85) + COORD_HALF) {
            return 0;
        }
        if ((entry_y >> 16) >= 10 && (entry_y >> 16) <= 11) {
            Game_SetScriptActive();
            g_SceneEventStep = 5;
        }
    }
    return 0;
}
