#include "area105_13.h"

MATCH void func_801F32B0(void) {
    if (D_80143F04 == 0x57) {
        if (D_80143F03 == 0) {
            SYS_SetFlag(g_SceneEventFlags, 0x4F);
        }
        if (D_80143F03 == 1) {
            SYS_ClearFlag(g_SceneEventFlags, 0x4F);
        }
    }
}
