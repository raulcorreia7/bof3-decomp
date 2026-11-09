#include "game_00.h"

MATCH void func_801A83DC(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0: {
            u8* game_state;
            game_state = &g_GameStateIndex;

            if (*game_state != GAME_REQUEST_MESSAGE) {
                /* Dest is the bit buffer at 0x80145548 (ahead of the celerity and bonebreak timers). */
                SYS_SetFlag(state + 0xC5C, g_SceneEventSelection);
                strncpy((char*)g_TextVariables[0], (char*)Message_GetText((g_SceneEventSelection + 0x4172)), 8);
                D_801490E0 = 0;
                Message_Request(0xFA);
                *game_state = GAME_REQUEST_MESSAGE;
                if (g_SndBGMId != GAME_NONE) {
                    SND_PauseBGM(g_SndBGMId);
                }
                SND_StartXAStream(9, 1);
                *state = 1;
                return;
            }
            return;
        }
        case 1:
            if ((SND_IsXAIdle() & BYTE_MASK) && (g_GameStateIndex != GAME_REQUEST_MESSAGE)) {
                if (g_SndBGMId != GAME_NONE) {
                    SND_ResumeBGM(g_SndBGMId);
                }
                g_ScriptWorkRecord->header.flags = 0;
                Game_ClearScriptActive();
                g_SceneEventMode      = SCENE_EVENT_NONE;
                *state                = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
