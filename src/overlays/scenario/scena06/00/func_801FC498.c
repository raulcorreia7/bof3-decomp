#include "scena06_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC498(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x1E;
                g_SceneState.step_05 = 1;
            }
            break;
        case 1: {
            u8* progress = g_ScriptVars;
            u8* stored;

            if (*progress != 0x1F) {
                break;
            }
            stored = &D_80144DF2;
            if ((u8)Item_Add(ITEM_CAT_WEAPON, *stored + 1, 1, 0) == 0) {
                *progress       = 0x20;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            } else {
                strncpy((char*)g_TextVariables[0], (char*)Item_GetRecord(ITEM_CAT_WEAPON, (u8)(*stored + 1)), ITEM_NAME_LENGTH);
                g_TextVariables[0][ITEM_NAME_LENGTH] = 0;
                MESSAGE_START_WAIT(MSG_148);
                SYS_SetFlag(g_SceneFlags, 0x22);
                SND_PlayCue(0x106);
                g_SceneState.step_05 = 0x15;
            }
            break;
        }
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x23;
                g_SceneState.step_05 = 0xC;
            }
            break;
        case 12: {
            u8* progress = g_ScriptVars;
            u8* stored;

            if (*progress != 0x24) {
                break;
            }
            stored = &D_80144DF5;
            if ((u8)Item_Add(ITEM_CAT_ARMOR, *stored + 1, 1, 0) == 0) {
                *progress       = 0x25;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            } else {
                strncpy((char*)g_TextVariables[1], (char*)Item_GetRecord(ITEM_CAT_ARMOR, (u8)(*stored + 1)), ITEM_NAME_LENGTH);
                g_TextVariables[1][ITEM_NAME_LENGTH] = 0;
                MESSAGE_START_WAIT(MSG_149);
                SYS_SetFlag(g_SceneFlags, 0x23);
                SND_PlayCue(0x106);
                g_SceneState.step_05 = 0x15;
            }
            break;
        }
        case 20:
            Message_Request(MSG_001);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
