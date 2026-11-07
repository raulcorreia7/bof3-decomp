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
                SND_PlayCue(0x202);
                func_801C16B8();
                UI_SetMode(9);
                *state = 2;
            }
            return;
        case 2:
            if (WINDOW_EFFECT_IDLE()) {
                Message_StartAreaMessage(1);
                g_GameStateIndex = 2;
                *state           = 3;
            }
            return;
        case 3:
            if (g_GameStateIndex != 2) {
                Game_ClearScriptActive();
                SYS_SetFlag(state + 0x63C, 0x74);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
