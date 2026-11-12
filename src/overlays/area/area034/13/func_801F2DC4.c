#include "area034_13.h"

MATCH s32 func_801F2DC4(void) {
    s32 bit;

    SYS_SetFlag(g_SceneEventFlags, 109);
    for (bit = 109; bit < 113; bit++) {
        if (SYS_TestFlag(g_SceneEventFlags, bit) == 0) {
            return 0;
        }
    }
    SYS_SetFlag(g_SceneEventFlags, 113);
    return 0;
}
