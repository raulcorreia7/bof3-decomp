#include "area062_13.h"

MATCH void func_801F2C7C(void) {
    s8* state;
    u8* record;
    u8  i;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            g_ScriptVars[0] = 0xA;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x0D));
            *state = 1;
            break;

        case 1:
            if (g_ScriptVars[0] == 0xB) {
                record = Item_GetRecord(0, 0x59);
                for (i = 0; i < 12; i++) {
                    g_TextVariables[0][i] = record[i];
                }
                D_801490E4[0] = 0;
                if (Item_Add(0, 0x59, 1, 0) & BYTE_MASK) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x06));
                    Message_Request(2);
                    SYS_SetFlag(g_SceneEventFlags, 104);
                } else {
                    Message_Request(3);
                }
                g_GameStateIndex = 2;
                g_SceneEventStep = 2;
            }
            break;

        case 2:
            if (g_GameStateIndex != *state) {
                Game_ClearScriptActive();
                g_ScriptVars[0]  = 0;
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
