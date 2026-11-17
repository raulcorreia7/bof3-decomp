#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F88DC(void) {
    u8* mode;

    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD_HALF(60), TO_COORD_HALF(55), AREA_ENTRY_MAP_LOADING | FACING_UP);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0xA);
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD_HALF(21), TO_COORD(35), FACING_RIGHT);
            g_GameRequestKind       = GAME_NONE;
            g_GameEntryMode         = 4;
            g_ScenarioState.step_05 = 2;
            break;
        case 2:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_ScenarioState.step_05 = 3;
            break;
        case 3:
            g_ScenarioState.timer_06--;
            if (g_ScenarioState.timer_06 != 0) {
                break;
            }
            UI_SetMode(1);
            g_AreaDrawFlags         = 0x1F;
            g_ScenarioState.step_05 = 4;
            g_ScriptVars[0]++;
            break;
        case 4:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD_HALF(60), TO_COORD(13), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
            g_ScenarioState.step_05 = 5;
            break;
        case 5:
            if (g_ScriptVars[0] != 0x18) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0xB);
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD(26), TO_COORD(25), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
            g_ScenarioState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] != 0x1B) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD(59), TO_COORD_HALF(54), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
            g_ScenarioState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 0x24) {
                break;
            }
            UI_SetMode(0);
            g_ScenarioState.step_05 = 8;
            break;
        case 8:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_AreaDrawFlags = 0;
            SCENARIO_MESSAGE_WAIT(MSG_021, 9);
            break;
        case 9:
            mode = &g_GameStateIndex;
            if (*mode == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_Characters[g_CharSlot[CHAR_ID_NINA_ADULT]].fatigue = 0;
            Char_RebuildPartyStats();
            SYS_ThreadWait(1);
            *mode                   = 6;
            g_ScenarioState.step_05 = 10;
            break;
        case 10:
            if (g_GameStateIndex != 0) {
                break;
            }
            Game_SetScriptActive();
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0xC);
            Game_RequestAreaChange(AREA_ID_OASIS, TO_COORD(60), TO_COORD(57), FACING_UP);
            g_GameRequestKind       = GAME_NONE;
            g_GameEntryMode         = GAME_NONE;
            g_ScenarioState.step_05 = 11;
            break;
        case 11:
            if (g_GameStateIndex != 0) {
                break;
            }
            g_AreaDrawFlags = 0x1F;
            UI_SetMode(1);
            g_ScenarioState.step_05 = 12;
            break;
        case 12:
            if (g_UiWindowEffectBusy) {
                break;
            }
            g_GameFlags &= 0xFFF7;
            Game_ClearScriptActive();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step_05  = 0;
            break;
    }
}
