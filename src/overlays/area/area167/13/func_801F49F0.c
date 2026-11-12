#include "area167_13.h"

MATCH void func_801F49F0(void) {
    if ((D_80143F03 == 0) && (SYS_TestFlag(g_SceneEventFlags, 143) != 0) && (SYS_TestFlag(g_SceneEventFlags, 144) == 0)) {
        g_AreaCameraOffsetZ = 0x980;
        g_SceneEventMode    = 0x20;
        g_SceneEventStep    = 0x1E;
    }
}
