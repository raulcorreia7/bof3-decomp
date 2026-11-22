#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB8A0(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScriptVars[0] = 0x0A;
            Scene_SetupParty(1);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 5);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_Actors[g_ScriptVars[3]].header.flags & ACTOR_FLAG_OFFSCREEN) {
                Scene_SetupParty(2);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 5:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA08_036, 6);
            break;
        case 6:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0x0A) {
                g_ScriptVars[0] = 0;
                SYS_SetFlag(g_SceneFlags, 6);
                Party_AddZenny(3000, 0);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
                Game_ClearScriptActive();
                Game_RequestAreaChange(AREA_ID_DAUNA_MINE_ADULT, TO_COORD(44), TO_COORD_HALF(14), FACING_RIGHT);
                g_GameFlags &= ~GAME_FLAG_SCROLL_LOCK;
            }
            break;
    }
}
