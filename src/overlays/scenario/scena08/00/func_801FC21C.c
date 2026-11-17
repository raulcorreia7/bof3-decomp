#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC21C(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScenarioState.timer_06-- == 0) {
                Scene_SetupParty(0);
                g_ScenarioState.step_05 = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 9);
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
        case 10:
            Game_RequestAreaChange(AREA_ID_MCNEIL, TO_COORD(92), TO_COORD_HALF(73), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 12) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_ScenarioState.step_05 = 12;
            }
            break;
        case 12:
            if (g_UiWindowEffectBusy == 0) {
                g_AreaDrawFlags = 0;
                Char_RebuildPartyStats();
                SND_PauseBGM(g_SndBGMId);
                SND_StartXAStream(0, 1);
                g_ScenarioState.step_05 = 13;
            }
            break;
        case 13:
            if (SND_IsXAIdle() != 0) {
                SND_ResumeBGM(g_SndBGMId);
                g_AreaDrawFlags = 0x1F;
                UI_SetMode(UI_MODE_FADE_IN);
                g_ScenarioState.step_05 = 14;
            }
            break;
        case 14:
            if (g_UiWindowEffectBusy == 0) {
                SYS_SetFlag(g_SceneFlags, 11);
                g_ScenarioState.step_05 = 15;
                g_ScriptVars[0]++;
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 0) {
                g_ScriptWorkRecord->unk_06 = 5;
                g_ScriptWorkRecord->unk_18 = 1;
                g_ScriptWorkRecord->unk_1C = 3;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;
    }
}
