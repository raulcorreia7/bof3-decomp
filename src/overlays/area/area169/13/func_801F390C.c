#include "area169_13.h"

MATCH void func_801F390C(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            UI_ModeSet(8);
            *state = 1;
            return;
        case 1:
            if (WINDOW_EFFECT_IDLE()) {
                SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 0x02));
                Char_RebuildPartyStats();
                UI_ModeSet(9);
                *state = 2;
            }
            return;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                MESSAGE_START_WAIT(MSG_AREA169_PARTY_HEALED);
                *state = 3;
            }
            return;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(state + 0x63C, 116);
                g_SceneEventState.mode = 0;
                *state                 = 0;
            }
            break;
    }
}
