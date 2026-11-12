#include "area167_13.h"

MATCH void func_801F42C4(void) {
    if (COORD_INT(g_Task->pos.z) != 960) {
        g_Task->header.flags &= ~0x40;
        if (D_80143F03 == 1) {
            SYS_SetFlag(g_SceneEventFlags, 72);
            SYS_ClearFlag(g_SceneEventFlags, 73);
        } else if (D_80143F03 == 2) {
            SYS_ClearFlag(g_SceneEventFlags, 72);
            SYS_SetFlag(g_SceneEventFlags, 73);
        } else if (D_80143F03 == 3) {
            SYS_ClearFlag(g_SceneEventFlags, 72);
            SYS_ClearFlag(g_SceneEventFlags, 73);
        }
    } else {
        g_ScriptState->cursor += 8;
    }
}
