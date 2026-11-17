#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9678(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            Scene_SetupParty(26);
            Area_StartScrollRoute(1);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x15) {
                Scene_SetupParty(5);
                g_ScenarioState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1F) {
                func_801BFE34(TO_COORD(5), TO_COORD(55), 9);
                Battle_StartScripted(9);
                g_ScenarioState.step_05 = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0x20) {
                Scene_SetupParty(21);
                g_ScenarioState.step_05 = 4;
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x25) {
                SYS_SetFlag(g_SceneFlags, 0x11);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_ScenarioState.step_05);
            }
            break;
    }
}
