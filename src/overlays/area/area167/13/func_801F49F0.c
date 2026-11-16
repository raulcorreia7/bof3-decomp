#include "area167_13.h"

MATCH void func_801F49F0(void) {
    if ((g_GameCellType == 0) && (SYS_TestFlag(g_SceneEventFlags, 143) != 0) && (SYS_TestFlag(g_SceneEventFlags, 144) == 0)) {
        g_AreaCameraOffsetZ    = 0x980;
        g_SceneEventState.mode = 0x20;
        g_SceneEventState.step = 0x1E;
    }
}
