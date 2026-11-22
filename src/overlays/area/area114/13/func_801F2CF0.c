#include "area114_13.h"

/* FAKE: the scene event reads stay on the symbol cells; as record members they moved the schedule. */
MATCH void func_801F2CF0(void) {
    switch (g_SceneEventStep) {
        case 0:
            g_SceneEventStep = func_801F2E48();
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 10:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                SND_BGMPause(g_SndBGMId);
                SND_XAStartStream(2, 1);
                g_SceneEventStep = 0xB;
            }
            break;
        case 11:
            if (SND_XAIsIdle() & BYTE_MASK) {
                if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                    SND_BGMResume(g_SndBGMId);
                    Game_ClearScriptActive();
                    g_ScriptWorkRecord->unk_7C = 9;
                    g_SceneEventMode           = 0;
                    g_SceneEventStep           = 0;
                }
            }
            break;
    }
}
