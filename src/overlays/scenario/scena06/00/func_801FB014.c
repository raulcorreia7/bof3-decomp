#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB014(void) {
    SpawnedActor* actor;
    s32           index;

    switch (g_ScenarioState.step_05) {
        case 0:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA06_012, 1);
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Area_CellSetCode(93, 46, 0);
            index = Actor_FindFreeSpawned() & BYTE_MASK;
            if (index != GAME_NONE) {
                actor               = &g_SpawnedActors[index];
                actor->header.flags = 1;
                actor->type         = 0x45;
            }
            SYS_ClearFlag(g_SceneFlags, 38);
            SYS_SetFlag(g_SceneFlags, 45);
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (!SYS_TestFlag(g_SceneFlags, 45)) {
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (SYS_TestFlag(g_SceneFlags, 38)) {
                g_ScenarioState.step_05 = 4;
            } else {
                g_ScenarioState.step_05 = 6;
            }
            break;
        case 4:
            Area_CellSetCode(93, 46, 81);
            SYS_SetFlag(g_SceneEventFlags, 47);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
            Scene_SetupParty(1);
            g_ScenarioState.step_05 = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 39);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            SND_BGMPlay(91, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            goto clear_script_state;
        case 6:
            Area_CellSetCode(93, 46, 81);
            if (!SYS_TestFlag(g_SceneFlags, 37)) {
                g_ScenarioState.step_05 = 7;
                break;
            }
            SYS_SetFlag(g_SceneEventFlags, 47);
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 4));
            SND_BGMPlay(91, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            Scene_SetupParty(2);
            SYS_ClearFlag(g_SceneFlags, 37);
            g_ScenarioState.step_05 = 8;
            break;
        case 7:
            SYS_ClearFlag(g_SceneEventFlags, 47);
            g_ScriptVars[0] = 0;
            goto clear_script_state;
        case 8:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            SYS_ClearFlag(g_SceneEventFlags, 47);
            goto clear_script_state;
    }
    return;

clear_script_state:
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    Game_ClearScriptActive();
    g_ScenarioState.step_05  = 0;
    g_ScenarioState.state_04 = 0;
}
