#include "area169_13.h"

MATCH void func_801F390C(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            UI_SetMode(8);
            *state = 1;
            return;
        case 1:
            if (WINDOW_EFFECT_IDLE()) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x02));
                Char_RebuildPartyStats();
                UI_SetMode(9);
                *state = 2;
            }
            return;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                Message_StartAreaMessage(1);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                *state           = 3;
            }
            return;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(state + 0x63C, 116);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
