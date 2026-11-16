#include "scena11_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7CC8(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScriptVars[0] = 1;
            Scene_SetupParty(4);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 6);
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        case 10:
            if (g_GameStateIndex == 2) {
                break;
            }
            if ((u16)Item_Count(0, 0x23, 0) == 0 || (u16)Item_Count(0, 0x24, 0) == 0 || (u16)Item_Count(0, 0x56, 0) == 0 || (u16)Item_Count(0, 0x4D, 0) == 0) {
                g_SceneState.step_05 = 0xB;
            } else {
                g_SceneState.step_05 = 0xF;
            }
            break;
        case 11:
            Message_StartAreaMessage(MSG_053);
            g_GameStateIndex     = 2;
            g_SceneState.step_05 = 0xC;
            break;
        case 12: {
            u8* progress;

            if (g_GameStateIndex == 2) {
                break;
            }
            progress = &g_ScriptVars[0];
            if (*progress != 6) {
                break;
            }
            Game_ClearScriptActive();
            *progress             = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
        }
        case 15:
            g_ScriptVars[0] = 1;
            Scene_SetupParty(5);
            g_SceneState.step_05 = 0x10;
            break;
        case 16:
            if (g_GameStateIndex == 2) {
                break;
            }
            if (g_ScriptVars[0] != 5) {
                break;
            }
            Game_ClearScriptActive();
            SYS_SetFlag(g_SceneFlags, 9);
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}
