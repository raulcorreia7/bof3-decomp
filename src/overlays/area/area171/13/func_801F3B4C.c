#include "area171_13.h"

MATCH void func_801F3B4C(void) {
    switch (g_SceneEventState.step) {
        case 0:
            if (g_GameCellType == 3) {
                UI_ModeSet(UI_MODE_WHITE_OUT);
                g_SceneEventState.step = 1;
            } else {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 1:
            if (!WINDOW_EFFECT_BUSY()) {
                SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 2));
                Char_RebuildPartyStats();
                UI_ModeSet(UI_MODE_WHITE_IN);
                g_SceneEventState.step = 2;
            }
            break;
        case 2:
            if (!WINDOW_EFFECT_BUSY()) {
                MESSAGE_START_WAIT(MSG_AREA171_PARTY_HEALED);
                g_SceneEventState.step = 3;
            }
            break;
        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneEventFlags, 0x74);
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 10:
            if (g_Game.members[0].u.field.mode.unsigned_value == 0) {
                Game_ClearScriptActive();
                Scene_SetupParty(0);
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            MESSAGE_START_WAIT(MSG_AREA171_PLANT_BLOCKS_ENTRANCE);
            g_SceneEventState.step = 0x15;
            break;
        case 21:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
