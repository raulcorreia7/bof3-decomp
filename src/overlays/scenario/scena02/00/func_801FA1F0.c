#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA1F0(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScriptVars[2]      = 1;
            g_ScenarioState.step = 1;
            Game_RequestAreaChange(0x1C, TO_COORD(0x38), TO_COORD(7), 0x80);
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                UI_ModeSet(UI_MODE_FADE_IN);
                g_AreaDrawFlags      = 0x1F;
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 6) {
                Area_ScrollStartRoute(0);
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 7) {
                g_ScriptVars[2]      = 1;
                g_ScenarioState.step = 7;
                Game_RequestAreaChange(0x1C, TO_COORD(0x37), TO_COORD(9), 0x81);
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 9) {
                SYS_SetFlag(g_SceneFlags, 0x15);
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 15:
            if (g_Game.members[1].u.field.mode.unsigned_value != 7) {
                Scene_SetupParty(2);
                g_ScenarioState.step = 0x10;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 2) {
                g_ScriptVars[2] = 1;
                Scene_RunScenario(0);
                g_ScenarioState.step = 0x11;
                SYS_SetFlag(g_SceneFlags, 1);
                Game_RequestAreaChange(0x1C, TO_COORD(0x28), TO_COORD(7), 0x83);
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 0x12) {
                g_GameFlags |= 8;
                Area_ScrollStartRoute(1);
                g_ScenarioState.step = 0x12;
            }
            break;
        case 18:
            if (g_ScriptVars[0] == 0x17) {
                if (Camera_TurnZ(0x5A, 2) == 0) {
                    g_ScenarioState.step = 0x13;
                    g_ScriptVars[3]      = 0;
                }
            }
            break;
        case 19:
            if (++g_ScriptVars[3] == 6) {
                g_ScriptVars[3]      = 0;
                g_ScriptVars[0]      = 0x18;
                g_ScenarioState.step = 0x14;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x18) {
                if (Camera_TurnZ(0x28, -2) == 0) {
                    g_ScenarioState.step = 0x15;
                }
            }
            break;
        case 21:
            if (g_ScriptVars[0] == 0x1A) {
                g_ScriptVars[2]      = 2;
                g_ScenarioState.step = 0x16;
                g_GameFlags ^= 8;
                Game_RequestAreaChange(0x1C, TO_COORD(0x27), TO_COORD(9), 0x84);
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 7) {
                g_ScriptVars[2] = 0;
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 3:
        case 4:
        case 5:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
            break;
    }
}
