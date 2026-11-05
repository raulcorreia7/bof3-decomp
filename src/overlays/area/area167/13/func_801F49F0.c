#include "area167_13.h"

MATCH void func_801F49F0(void) {
    if ((D_80143F03 == 0) && (SYS_TestFlag(g_SceneEventFlags, 0x8F) != 0) &&
        (SYS_TestFlag(g_SceneEventFlags, 0x90) == 0)) {
        g_AreaCameraOffsetZ = 0x980;
        D_801448EB          = 0x20;
        D_801448EC          = 0x1E;
    }
}
