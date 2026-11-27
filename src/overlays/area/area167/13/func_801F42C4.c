#include "area167_13.h"

MATCH void func_801F42C4(void) {
    if (COORD_INT(SELF(Actor)->pos.z) != 960) {
        SELF(Actor)->header.flags &= ~0x40;
        if (g_GameCellType == 1) {
            SYS_SetFlag(g_SceneEventFlags, 72);
            SYS_ClearFlag(g_SceneEventFlags, 73);
        } else if (g_GameCellType == 2) {
            SYS_ClearFlag(g_SceneEventFlags, 72);
            SYS_SetFlag(g_SceneEventFlags, 73);
        } else if (g_GameCellType == 3) {
            SYS_ClearFlag(g_SceneEventFlags, 72);
            SYS_ClearFlag(g_SceneEventFlags, 73);
        }
    } else {
        g_ScriptState->cursor += 8;
    }
}
