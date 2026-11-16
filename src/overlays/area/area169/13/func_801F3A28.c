#include "area169_13.h"

MATCH s32 func_801F3A28(void) {
    if (g_GameCellType == 1) {
        if (!SYS_TestFlag(g_SceneEventFlags, 116)) {
            Scene_StartEvent(0x2F, 0);
            return 1;
        }
    }
    return 0;
}
