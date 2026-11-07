#include "area048_13.h"

MATCH s32 func_801F4C28(s32 arg0, s32 arg1) {
    if ((arg0 >> 16) == 0x17 && (u32)((arg1 >> 16) - 0xD) < 2) {
        g_SceneEventMode      = 3;
        g_SceneEventSelection = 0;
        Game_SetScriptActive();
    }

    if ((arg1 >> 16) == 6 || arg1 == 0x58000) {
        if ((u32)((arg0 >> 16) - 0xC) < 2) {
            g_SceneEventMode      = 3;
            g_SceneEventSelection = 1;
            Game_SetScriptActive();
        }
    }

    if ((arg1 >> 16) == 0xB || arg1 == 0xA8000) {
        if ((u32)((arg0 >> 16) - 0x13) < 2) {
            g_SceneEventMode      = 3;
            g_SceneEventSelection = 2;
            Game_SetScriptActive();
        }
    }
    return 0;
}
