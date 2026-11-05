#include "area109_13.h"

MATCH s32 func_801F2D04(void) {
    s32 i;
    s32 flags;

    flags = 0;
    i     = 0;
    do {
        if (SYS_TestFlag(g_SceneEventFlags, D_801F2E90[i]) != 0) {
            flags |= 1 << i;
        }
        i++;
    } while (i < 3);
    return flags + 1;
}
