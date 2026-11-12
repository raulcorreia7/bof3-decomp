#include "area167_13.h"

MATCH void func_801F4140(void) {
    if (D_80143F03 == 2) {
        if (SYS_TestFlag(g_SceneEventFlags, 74)) {
            SYS_ClearFlag(g_SceneEventFlags, 74);
            g_ScriptState->cursor = 0xFFFE;
            if (D_80143F06 == 0) {
                g_ScriptState->pad_03 = 7;
                return;
            }
            g_ScriptState->pad_03 = 8;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 72) == 0) {
            if (SYS_TestFlag(g_SceneEventFlags, 73) == 0) {
                COORD_INT(g_Task->pos.z) = 2496;
            } else {
                COORD_INT(g_Task->pos.z) = -0x240;
            }
            g_Task->header.flags |= 0x40;
            return;
        }
    }

    if (D_80143F03 == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 74)) {
            SYS_ClearFlag(g_SceneEventFlags, 74);
            g_ScriptState->pad_03 = 7;
            g_ScriptState->cursor = 0xFFFE;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 73) == 0) {
            COORD_INT(g_Task->pos.z) = 2496;
            g_Task->header.flags |= 0x40;
            return;
        }
    }

    COORD_INT(g_Task->pos.z) = 960;
}
