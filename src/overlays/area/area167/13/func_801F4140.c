#include "area167_13.h"

MATCH void func_801F4140(void) {
    if (g_GameCellType == 2) {
        if (SYS_TestFlag(g_SceneEventFlags, 74)) {
            SYS_ClearFlag(g_SceneEventFlags, 74);
            g_ScriptState->cursor = 0xFFFE;
            if (g_GameLastCellType == 0) {
                g_ScriptState->script_index = 7;
                return;
            }
            g_ScriptState->script_index = 8;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 72) == 0) {
            if (SYS_TestFlag(g_SceneEventFlags, 73) == 0) {
                COORD_INT(SELF(Actor)->pos.z) = 2496;
            } else {
                COORD_INT(SELF(Actor)->pos.z) = -0x240;
            }
            SELF(Actor)->header.flags |= 0x40;
            return;
        }
    }

    if (g_GameCellType == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 74)) {
            SYS_ClearFlag(g_SceneEventFlags, 74);
            g_ScriptState->script_index = 7;
            g_ScriptState->cursor       = 0xFFFE;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 73) == 0) {
            COORD_INT(SELF(Actor)->pos.z) = 2496;
            SELF(Actor)->header.flags |= 0x40;
            return;
        }
    }

    COORD_INT(SELF(Actor)->pos.z) = 960;
}
