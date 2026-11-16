#include "area048_13.h"

MATCH s32 func_801F4C28(s32 x, s32 y) {
    if ((x >> 16) == 0x17 && (u32)((y >> 16) - 0xD) < 2) {
        g_SceneEventState.mode      = 3;
        g_SceneEventState.selection = 0;
        Game_SetScriptActive();
    }

    if ((y >> 16) == 6 || y == 360448) {
        if ((u32)((x >> 16) - 0xC) < 2) {
            g_SceneEventState.mode      = 3;
            g_SceneEventState.selection = 1;
            Game_SetScriptActive();
        }
    }

    if ((y >> 16) == 0xB || y == 688128) {
        if ((u32)((x >> 16) - 0x13) < 2) {
            g_SceneEventState.mode      = 3;
            g_SceneEventState.selection = 2;
            Game_SetScriptActive();
        }
    }
    return 0;
}
