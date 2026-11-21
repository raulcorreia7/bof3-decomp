#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9874(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            if (g_Game.members[0].chr.character_id != CHAR_ID_REI) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA01_007, 1);
            } else {
                Scene_SetupParty(0);
                SCENARIO_MESSAGE_WAIT(MSG_SCENA01_008, 2);
            }
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SCRIPT_VARS_CLEAR_ALL();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_PlaySE(0x103);
                g_ScenarioState.step_05 = 10;
                g_GameFlags |= 0x1E;
            }
            break;
        case 10:
            Game_SetScriptActive();
            g_ScenarioState.step_05 = 11;
            Game_RequestAreaChange(8, 0x540000, 0x1D0000, 0x81);
            g_GamePrevSelection = 11;
            break;
        case 11:
            g_ScriptVars[0] = 2;
            Area_StartScrollRoute(0);
            g_ScenarioState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] == 0x16) {
                SYS_SetFlag(g_SceneFlags, 4);
                g_ScriptVars[1] = 1;
                SCENARIO_RETURN_TO_START();
                g_ScriptVars[2] = 2;
                Game_ClearScriptActive();
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                g_GameFlags |= 0x80;
                Item_Add(ITEM_CATEGORY_ITEM, ITEM_PLATE, 1, 0);
            }
            break;
    }
}
