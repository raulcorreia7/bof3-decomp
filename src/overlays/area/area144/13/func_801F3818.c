#include "area144_13.h"

MATCH void func_801F3818(void) {
    if (SYS_TestFlag(g_SceneFlags, 23) == 0) {
        g_ScriptState->pad_03 = 2;
        g_ScriptState->cursor = 0xFFFE;
    } else if (SYS_TestFlag(g_SceneFlags, 24) == 0) {
        if (g_Game.members[0].chr.character_id != CHAR_ID_GARR) {
            g_ScriptState->pad_03 = 3;
        } else {
            g_ScriptState->pad_03 = 4;
            SYS_SetFlag(g_SceneFlags, 24);
        }
    } else if (SYS_TestFlag(g_SceneFlags, 25) == 0) {
        if (g_Game.members[0].chr.character_id == CHAR_ID_NINA_ADULT) {
            g_ScriptState->pad_03 = 7;
            SYS_SetFlag(g_SceneFlags, 25);
        } else if (g_Game.members[0].chr.character_id == CHAR_ID_MOMO) {
            g_ScriptState->pad_03 = 6;
        } else {
            g_ScriptState->pad_03 = 5;
        }
    } else if (SYS_TestFlag(g_SceneFlags, 26) == 0) {
        if (g_Game.members[0].chr.character_id == CHAR_ID_RYU_ADULT) {
            g_ScriptState->pad_03 = 0xA;
        } else if (g_Game.members[0].chr.character_id == CHAR_ID_NINA_ADULT) {
            g_ScriptState->pad_03 = 9;
        } else {
            g_ScriptState->pad_03 = 8;
        }
    } else if (SYS_TestFlag(g_SceneFlags, 27) == 0) {
        if (g_Game.members[0].chr.character_id == CHAR_ID_RYU_ADULT) {
            g_ScriptState->pad_03 = 0xD;
            SYS_SetFlag(g_SceneFlags, 27);
        } else {
            g_ScriptState->pad_03 = 0xC;
        }
    }
    g_ScriptState->cursor = 0xFFFE;
}
