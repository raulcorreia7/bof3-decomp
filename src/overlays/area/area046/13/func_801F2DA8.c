#include "area046_13.h"

MATCH s32 func_801F2DA8(void) {
    s32 bit;

    SYS_SetFlag(g_SceneEventFlags, 0x70);
    for (bit = 109; bit < 113; bit++) {
        if (SYS_TestFlag(g_SceneEventFlags, bit) == 0) {
            return 0;
        }
    }
    SYS_SetFlag(g_SceneEventFlags, 0x71);
    return 0;
}
