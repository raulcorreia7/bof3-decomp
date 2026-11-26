#include "scena08_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB168(void) {
    u8* step;

    step = &g_ScenarioState.step;
    switch (*step) {
        case 0:
            g_PartyActors[0].unk_77 = 3;
            g_PartyActors[0].unk_7E = 0;
            *step                   = 1;
            break;
        case 1:
            if (g_ScriptVars[3] == 0x12) {
                g_ScenarioState.timer_06 = 0x10;
                *step                    = 2;
            }
            break;
        case 2:
            if (g_ScenarioState.timer_06-- == 0) {
                SYS_SetFlag(g_SceneFlags, 3);
                D_801448EE               = 1;
                g_SceneEventState.mode   = SCENE_EVENT_MINE_ENTRY;
                g_SceneEventState.step   = 3;
                g_ScenarioState.state_04 = 0;
                *step                    = 0;
            }
            break;
    }
}
