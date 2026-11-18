#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8564(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScriptVars[2]         = 2;
            g_ScenarioState.step_05 = 1;
            func_8019FA28(0x34, TO_COORD(0x3E), TO_COORD(0x27), 0x84);
            g_GamePrevSelection = 0xFF;
            break;
        case 1:
            if (g_ScriptVars[0] == 3) {
                func_801C601C(0);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0xD) {
                func_801BFE34(TO_COORD(0x3E), TO_COORD(0x20), 0x11);
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xF) {
                func_801C7A54(0x11);
                g_ScenarioState.step_05 = 7;
            }
            break;
        case 7:
            if (g_ScriptVars[0] == 0x14) {
                Scene_SetupParty(0);
                g_ScenarioState.step_05 = 8;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x16) {
                g_ScriptVars[2]         = 3;
                g_ScenarioState.step_05 = 9;
                SYS_SetFlag(g_SceneFlags, 5);
                func_8019FA28(0x34, TO_COORD(0x85), TO_COORD(0xF), 0x85);
                g_GamePrevSelection = 0x3B;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 8) {
                g_GameFlags |= 0x20;
                SYS_SetFlag(g_SceneFlags, 6);
                Game_ClearScriptActive();
                g_ScriptVars[1]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScenarioState.step_05  = 0;
                g_ScenarioState.state_04 = 5;
            }
            break;
        case 20:
            MESSAGE_START_WAIT(MSG_SCENA05_011);
            g_ScenarioState.step_05 = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[2]          = 0;
                g_ScenarioState.step_05  = 0;
                g_ScenarioState.state_04 = 5;
            }
            break;
    }
}
