#include "area167_13.h"

MATCH void func_801F3F58(void) {
    if (g_GameCellType == 2) {
        if (SYS_TestFlag(g_SceneEventFlags, 76)) {
            SYS_ClearFlag(g_SceneEventFlags, 76);
            g_ScriptState->script_index = 5;
            g_ScriptState->cursor       = 0xFFFE;
            return;
        }
        if (!SYS_TestFlag(g_SceneEventFlags, 75)) {
            COORD_INT(SELF(Actor)->pos.z) = -0x240;
            SELF(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
            return;
        }
    }
    if (g_GameCellType == 1) {
        if (SYS_TestFlag(g_SceneEventFlags, 76)) {
            SYS_ClearFlag(g_SceneEventFlags, 76);
            g_ScriptState->script_index = 4;
            g_ScriptState->cursor       = 0xFFFE;
            return;
        }
        if (SYS_TestFlag(g_SceneEventFlags, 75)) {
            COORD_INT(SELF(Actor)->pos.z) = 2496;
            SELF(Actor)->header.flags |= ACTOR_FLAG_HIDDEN;
            return;
        }
    }
    COORD_INT(SELF(Actor)->pos.z) = 960;
}
