#include "scena03_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA0A4(void) {
    u16 timer;

    switch (g_ScenarioState.step_05) {
        case 0:
            Scene_SetupParty(0);
            g_ScenarioState.step_05 = 1;
            break;

        case 1:
            if (g_ScriptVars[0] == 4) {
                UI_SetMode(0);
                g_ScenarioState.timer_06 = 60;
                g_ScenarioState.step_05  = 2;
            }
            break;

        case 2:
            if (g_UiWindowEffectBusy == 0) {
                Message_StartAreaMessage(MSG_032);
                g_GameStateIndex        = 2;
                g_AreaDrawFlags         = 0;
                g_ScenarioState.step_05 = 3;
            }
            break;

        case 3:
            if (g_GameStateIndex != 2) {
                Game_RequestAreaChange(AREA_ID_WYNDIA_LOWER, TO_COORD(45), TO_COORD(40), 0x81);
                g_GameEntryMode         = 0xFF;
                g_ScenarioState.step_05 = 4;
            }
            break;

        case 4:
            if (g_UiWindowEffectBusy == 0) {
                g_ScriptVars[0]++;
                Game_ClearScriptActive();
                g_ScenarioState.step_05 = 5;
            }
            break;

        case 5:
            if (g_GameStateIndex == 2 && g_MessageRequest == 0x33) {
                g_ScenarioState.step_05 = 10;
            }
            break;

        case 6:
            timer = g_ScenarioState.timer_06;
            if (timer != 0) {
                g_ScenarioState.timer_06 = timer - 1;
                break;
            }
            Game_SetScriptActive();
            SYS_SetFlag(g_SceneFlags, 0x15);
            g_ScriptVars[0] = 1;
            Game_RequestAreaChange(AREA_ID_WYNDIA_LOWER, TO_COORD(45), TO_COORD(40), 0x82);
            g_ScenarioState.step_05 = 7;
            break;

        case 7:
            if (g_UiWindowEffectBusy == 0) {
                g_ScenarioState.step_05 = 8;
                g_ScriptVars[0]++;
            }
            break;

        case 8:
            if (g_ScriptVars[0] == 0xF) {
                g_ScriptVars[0] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step_05  = 0;
            }
            break;

        case 9:
            break;

        case 10:
            if (g_GameStateIndex != 2) {
                g_ScenarioState.step_05 = 5;
                D_80146258 &= ~0x100;
            }
            break;
    }
}
