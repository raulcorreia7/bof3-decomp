#include "area130_13.h"

MATCH void func_801F3CD0(void) {
    u8* record;

    switch (g_SceneState.step_05) {
        case 0:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            switch (g_Characters[CHAR_INDEX_WHELP].abilities.skill[0]) {
                case 0:
                    record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_AMMONIA);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_ITEM, ITEM_AMMONIA, 1, 0);
                    break;
                case 1:
                    record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_WISDOM_SEED);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_ITEM, ITEM_WISDOM_SEED, 1, 0);
                    break;
                case 2:
                    record = Item_GetRecord(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_ITEM, ITEM_WISDOM_FRUIT, 1, 0);
                    break;
                case 3:
                    record = Item_GetRecord(ITEM_CAT_ARMOR, ARMOR_LACQUER_ARMOR);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_ARMOR, ARMOR_LACQUER_ARMOR, 1, 0);
                    break;
                case 4:
                    record = Item_GetRecord(ITEM_CAT_WEAPON, WEAPON_BARBAROSSA);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_WEAPON, WEAPON_BARBAROSSA, 1, 0);
                    break;
                case 5:
                    record = Item_GetRecord(ITEM_CAT_ACCESSORY, ACCESSORY_SHAMANS_RING);
                    strncpy((char*)g_TextVariables[0], (char*)record, ITEM_NAME_LENGTH);
                    Item_Add(ITEM_CAT_ACCESSORY, ACCESSORY_SHAMANS_RING, 1, 0);
                    break;
            }
            g_TextVariables[0][ITEM_NAME_LENGTH] = 0;
            g_TextVariables[1][8]                = 0;
            Message_StartAreaMessage(0x49);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            SYS_SetFlag(g_SceneEventFlags, 0x98);
            Game_ClearScriptActive();
            g_SceneEventMode      = 0;
            g_SceneEventSelection = 0;
            break;
    }
}
