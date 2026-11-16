#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB6C4(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[0] = 0x15;
            SYS_SetFlag(g_SceneFlags, 0x27);
            Item_Remove(ITEM_CAT_VITAL, VITAL_ITEM_WALLET, 1, 0);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 0x16) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 10:
            g_ScriptVars[0] = 0x14;
            SYS_SetFlag(g_SceneFlags, 0x26);
            Item_Add(ITEM_CAT_VITAL, VITAL_ITEM_WALLET, 1, 0);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 15:
            SCENE_MESSAGE_WAIT(115, 16);
            break;
        case 16:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801FCD14(145);
                g_SceneState.step_05 = 17;
                g_ScriptVars[0]      = 0x19;
            }
            break;
        case 17:
            if (g_ScriptVars[0] == 0x1A) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                g_ScriptVars[2] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
