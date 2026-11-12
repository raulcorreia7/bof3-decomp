#include "area171_13.h"

MATCH void func_801F3B4C(void) {
    switch (g_SceneEventStep) {
        case 0:
            if (D_80143F03 == 3) {
                UI_SetMode(UI_MODE_WHITE_OUT);
                g_SceneEventStep = 1;
            } else {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 1:
            if (!WINDOW_EFFECT_BUSY()) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
                func_801C16B8();
                UI_SetMode(UI_MODE_WHITE_IN);
                g_SceneEventStep = 2;
            }
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                Message_StartAreaMessage(1);
                g_GameStateIndex = GAME_REQUEST_MESSAGE;
                g_SceneEventStep = 3;
            }
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneEventFlags, 0x74);
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 10:
            if (g_Game.members[0].u.field.mode_12B.u8_value == 0) {
                Game_ClearScriptActive();
                func_801BE1B0(0);
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            Message_StartAreaMessage(2);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            g_SceneEventStep = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }
}
