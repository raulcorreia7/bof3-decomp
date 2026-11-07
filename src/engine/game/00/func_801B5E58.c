#include "game_00.h"

MATCH void func_801B5E58(s32 cue_value) {
    SND_PlayCue(EMI_CUE_ID(1, 6));
    TEXT_Format(g_TextVariables[0], D_80195FBC, cue_value);
    Resource_RequestArea(5);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    Party_AddZenny(cue_value, 0);
}
