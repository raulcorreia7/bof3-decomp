#include "area169_13.h"

MATCH s32 func_801F3A28(void) {
    if (D_80143F03 == 1) {
        if (!SYS_TestFlag(g_SceneEventFlags, 0x74)) {
            Game_SetScriptActive();
            g_SceneEventMode = 0x2F;
            g_SceneEventStep = 0;
            return 1;
        }
    }
    return 0;
}
