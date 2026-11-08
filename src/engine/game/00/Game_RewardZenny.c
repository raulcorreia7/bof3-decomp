#include "game_00.h"

/* func_801B5E58 */
MATCH void Game_RewardZenny(s32 zenny) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
    TEXT_Format(g_TextVariables[0], D_80195FBC, zenny);
    Message_Request(5);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    Party_AddZenny(zenny, 0);
}
