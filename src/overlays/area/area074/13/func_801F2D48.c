#include "area074_13.h"

MATCH void func_801F2D48(void) {
    u8 dir;

    g_CurrentActor->interaction_flags &= 0xFE;
    if (g_Game.members[0].chr.character_id != 2) {
        return;
    }
    dir = g_Game.members[0].facing & 0x7;
    if (TASK(Actor)->timer != 0) {
        return;
    }
    if (dir != 5 && dir != 1) {
        return;
    }
    TASK(Actor)->direction = dir;
    if (Actor_IsAheadBlocked(g_CurrentActor)) {
        return;
    }
    g_CurrentActor->unk_7B = 3;
    Area_MoveActorRoute(g_ScriptState, dir);
    if (dir == 5) {
        if (SYS_TestFlag(&g_Scenario2Flags[0x28], 6) != 0) {
            SYS_ClearFlag(&g_Scenario2Flags[0x28], 6);
        } else {
            SYS_SetFlag(&g_Scenario2Flags[0x28], 5);
        }
    } else {
        SYS_SetFlag(&g_Scenario2Flags[0x28], 6);
    }
    SND_PLAY_SE_ID(g_Game.members[0].unk_2C.value + 0x100);
}
