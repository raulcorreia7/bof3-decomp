#include "area167_13.h"

MATCH void func_801F3F58(void) {
    if (D_80143F03 == 2) {
        if (SYS_TestFlag(g_SceneEventFlags, 76)) {
            SYS_ClearFlag(g_SceneEventFlags, 76);
            g_ScriptState->pad_03 = 5;
            g_ScriptState->cursor = 0xFFFE;
            return;
        }
        if (!SYS_TestFlag(g_SceneEventFlags, 75)) {
            COORD_INT(g_Task->pos.z) = -0x240;
            g_Task->header.flags |= ACTOR_FLAG_HIDDEN;
            return;
        }
    }
    if (D_80143F03 == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 76)) {
            SYS_ClearFlag(g_SceneEventFlags, 76);
            g_ScriptState->pad_03 = 4;
            g_ScriptState->cursor = 0xFFFE;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 75)) {
            COORD_INT(g_Task->pos.z) = 2496;
            g_Task->header.flags |= ACTOR_FLAG_HIDDEN;
            return;
        }
    }
    COORD_INT(g_Task->pos.z) = 960;
}
