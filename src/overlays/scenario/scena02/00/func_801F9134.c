#include "scena02_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9134(void) {
    switch (g_ScenarioState.step) {
        case 0:
            Game_SetScriptActive();
            Scene_SetupParty(3);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[2]      = 4;
                g_ScenarioState.step = 3;
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, TO_COORD(64), TO_COORD(27), 0x94);
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 9) {
                SYS_SetFlag(g_SceneFlags, 0xF);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 5:
            Scene_SetupParty(4);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 1) {
                Area_ScrollStartRoute(0);
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 2) {
                func_801BFE34(0x200000, 0x260000, 8);
                g_ScenarioState.step = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x10) {
                Game_BattleStartScripted(8);
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 0x11) {
                Scene_SetupParty(0x12);
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0x14) {
                SYS_SetFlag(g_SceneFlags, 0x10);
                Game_ClearScriptActive();
                SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
