#include "game_00.h"

/* func_801B5E58 */
MATCH void Game_RewardZenny(s32 cue_value) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    TEXT_Format(g_TextVariables[0], D_80195FBC, cue_value);
    Message_Request(5);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    Party_AddZenny(cue_value, 0);
}
