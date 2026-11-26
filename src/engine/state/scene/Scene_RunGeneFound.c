#include "engine/game/00/game_00.h"

/* func_801A83DC */
/* Sets the found gene's flag, shows the found-gene message and plays the XA stream with the BGM paused. */
MATCH void Scene_RunGeneFound(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0: {
            u8* game_state;
            game_state = &g_GameStateIndex;

            if (*game_state != GAME_REQUEST_MESSAGE) {
                /* kept as step + 0xC5C = g_SaveData.found_genes: the member's absolute address lengthens the function */
                SYS_SetFlag(state + 0xC5C, g_SceneEventState.selection);
                strncpy((char*)g_TextVariables[0], (char*)UI_MessageGetText((g_SceneEventState.selection + 0x4172)), 8);
                D_801490E0 = 0;
                UI_MessageRequest(MSG_SYSTEM_FOUND_GENE);
                *game_state = GAME_REQUEST_MESSAGE;
                if (g_SndBGMId != GAME_NONE) {
                    SND_BGMPause(g_SndBGMId);
                }
                SND_XAStartStream(9, 1);
                *state = 1;
                return;
            }
            return;
        }
        case 1:
            if ((SND_XAIsIdle() & BYTE_MASK) && (g_GameStateIndex != GAME_REQUEST_MESSAGE)) {
                if (g_SndBGMId != GAME_NONE) {
                    SND_BGMResume(g_SndBGMId);
                }
                g_ScriptWorkRecord->header.flags = 0;
                Game_ClearScriptActive();
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                *state                      = 0;
                g_SceneEventState.selection = 0;
            }
            break;
    }
}
