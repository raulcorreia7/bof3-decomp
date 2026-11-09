#include "engine/slus/slus.h"

/* returns the game-state word that `kind` selects. */
MATCH s32 func_8015B870(u32 kind) {
    switch (kind & BYTE_MASK) {
        case 0:
        case 14:
            return g_SceneRecord.sbyte;
        case 1:
            return g_GameAreaId;
        case 2:
            return *g_SceneFlags;
        case 3:
            return g_ScriptVars[0];
        case 4:
            return g_ScriptVars[1];
        case 5:
            return g_ScriptVars[2];
        case 6:
            return g_ScriptVars[3];
        case 7:
            /* FAKE: retail reads g_SceneState.state_04 as RecordKey. */
            return (*(RecordKey*)&g_SceneState.state_04).sbyte;
        case 8:
            return D_80143F03;
        case 9:
            return g_SceneState.flags_01 & 1;
        case 10:
            return g_Task->script_pc;
        case 11:
            return g_Game.members[0].chr.character_id;
        case 12:
            /* FAKE: retail reads g_SceneEventFlags as u32. */
            return (*(u32*)g_SceneEventFlags);
        case 13:
            return 1;
        default:
            return 0xFF;
    }
}
