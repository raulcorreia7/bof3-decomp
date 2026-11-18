#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB6C4(void) {
    switch (g_ScenarioState.step_05) {
        case 0:
            g_ScriptVars[0] = 0x15;
            SYS_SetFlag(g_SceneFlags, 0x27);
            Item_Remove(ITEM_CATEGORY_VITAL, VITAL_ITEM_WALLET, 1, 0);
            g_ScenarioState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x16) {
                SCRIPT_VARS_CLEAR_ALL();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
        case 10:
            g_ScriptVars[0] = 0x14;
            SYS_SetFlag(g_SceneFlags, 0x26);
            Item_Add(ITEM_CATEGORY_VITAL, VITAL_ITEM_WALLET, 1, 0);
            Game_ClearScriptActive();
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            SCENARIO_RETURN_TO_START();
            break;
        case 15:
            SCENARIO_MESSAGE_WAIT(MSG_SCENA02_115, 16);
            break;
        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801FCD14(145);
                g_ScenarioState.step_05 = 17;
                g_ScriptVars[0]         = 0x19;
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 0x1A) {
                SCRIPT_VARS_CLEAR_ALL();
                Game_ClearScriptActive();
                SCENARIO_RETURN_TO_START();
            }
            break;
    }
}
