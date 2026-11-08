#include "area144_13.h"

MATCH void func_801F3818(void) {
    if (SYS_TestFlag(g_SceneFlags, 0x17) == 0) {
        g_ScriptState->pad_03 = 2;
        g_ScriptState->cursor = 0xFFFE;
    } else if (SYS_TestFlag(g_SceneFlags, 0x18) == 0) {
        if (g_Game.members[0].chr.character_id != 2) {
            g_ScriptState->pad_03 = 3;
        } else {
            g_ScriptState->pad_03 = 4;
            SYS_SetFlag(g_SceneFlags, 0x18);
        }
    } else if (SYS_TestFlag(g_SceneFlags, 0x19) == 0) {
        if (g_Game.members[0].chr.character_id == 8) {
            g_ScriptState->pad_03 = 7;
            SYS_SetFlag(g_SceneFlags, 0x19);
        } else if (g_Game.members[0].chr.character_id == 5) {
            g_ScriptState->pad_03 = 6;
        } else {
            g_ScriptState->pad_03 = 5;
        }
    } else if (SYS_TestFlag(g_SceneFlags, 0x1A) == 0) {
        if (g_Game.members[0].chr.character_id == 7) {
            g_ScriptState->pad_03 = 0xA;
        } else if (g_Game.members[0].chr.character_id == 8) {
            g_ScriptState->pad_03 = 9;
        } else {
            g_ScriptState->pad_03 = 8;
        }
    } else if (SYS_TestFlag(g_SceneFlags, 0x1B) == 0) {
        if (g_Game.members[0].chr.character_id == 7) {
            g_ScriptState->pad_03 = 0xD;
            SYS_SetFlag(g_SceneFlags, 0x1B);
        } else {
            g_ScriptState->pad_03 = 0xC;
        }
    }
    g_ScriptState->cursor = 0xFFFE;
}
