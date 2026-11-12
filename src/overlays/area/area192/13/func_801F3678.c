#include "area192_13.h"

MATCH void func_801F3678(void) {
    u8* flag;

    if (SYS_TestFlag(g_SceneEventFlags, 119)) {
        flag       = &g_SceneState.flags_01;
        D_80144F54 = 0x1E0;
        D_80146880 = 0;
        D_80146881 = 0;
        *flag      = *flag & 0xFE;
        Actor_Clear();
    }
}
