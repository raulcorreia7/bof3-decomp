#include "scena06_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC498(void) {
    switch (g_ScenarioState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x1E;
                g_ScenarioState.step = 1;
            }
            break;
        case 1: {
            u8* progress = g_ScriptVars;
            u8* stored;

            if (*progress != 0x1F) {
                break;
            }
            stored = &g_Characters[7].equip.weapon;
            if ((u8)Item_Add(ITEM_CATEGORY_WEAPON, *stored + 1, 1, 0) == 0) {
                *progress       = 0x20;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            } else {
                strncpy((char*)g_TextVariables[0], (char*)Item_GetRecord(ITEM_CATEGORY_WEAPON, (u8)(*stored + 1)), ITEM_NAME_LENGTH);
                g_TextVariables[0][ITEM_NAME_LENGTH] = 0;
                MESSAGE_START_WAIT(MSG_SCENA06_148);
                SYS_SetFlag(g_SceneFlags, 0x22);
                SND_SEPlay(0x106);
                g_ScenarioState.step = 0x15;
            }
            break;
        }
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0]      = 0x23;
                g_ScenarioState.step = 0xC;
            }
            break;
        case 12: {
            u8* progress = g_ScriptVars;
            u8* stored;

            if (*progress != 0x24) {
                break;
            }
            stored = &g_Characters[7].equip.armor;
            if ((u8)Item_Add(ITEM_CATEGORY_ARMOR, *stored + 1, 1, 0) == 0) {
                *progress       = 0x25;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            } else {
                strncpy((char*)g_TextVariables[1], (char*)Item_GetRecord(ITEM_CATEGORY_ARMOR, (u8)(*stored + 1)), ITEM_NAME_LENGTH);
                g_TextVariables[1][ITEM_NAME_LENGTH] = 0;
                MESSAGE_START_WAIT(MSG_SCENA06_149);
                SYS_SetFlag(g_SceneFlags, 0x23);
                SND_SEPlay(0x106);
                g_ScenarioState.step = 0x15;
            }
            break;
        }
        case 20:
            UI_MessageRequest(MSG_SYSTEM_NOTHING_FOUND);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
    }
}
