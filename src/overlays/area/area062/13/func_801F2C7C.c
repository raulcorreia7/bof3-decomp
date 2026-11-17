#include "area062_13.h"

MATCH void func_801F2C7C(void) {
    s8* state;
    u8* record;
    u8  i;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            g_ScriptVars[0] = 0xA;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x0D));
            *state = 1;
            break;

        case 1:
            if (g_ScriptVars[0] == 0xB) {
                record = Item_GetRecord(ITEM_CATEGORY_ITEM, ITEM_FLOWER_JEWEL);
                for (i = 0; i < 12; i++) {
                    g_TextVariables[0][i] = record[i];
                }
                D_801490E4[0] = 0;
                if (Item_Add(ITEM_CATEGORY_ITEM, ITEM_FLOWER_JEWEL, 1, 0) & BYTE_MASK) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
                    Message_Request(MSG_002);
                    SYS_SetFlag(g_SceneEventFlags, 104);
                } else {
                    Message_Request(MSG_003);
                }
                g_GameStateIndex       = GAME_REQUEST_MESSAGE;
                g_SceneEventState.step = 2;
            }
            break;

        case 2:
            if (g_GameStateIndex != *state) {
                Game_ClearScriptActive();
                g_ScriptVars[0]        = 0;
                g_SceneEventState.mode = 0;
                *state                 = 0;
            }
            break;
    }
}
