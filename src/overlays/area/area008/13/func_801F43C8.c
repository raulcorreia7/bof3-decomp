#include "area008_13.h"

MATCH void func_801F43C8(void) {
    TEXT_Format(g_TextVariables[0], D_801F2C14, g_ScriptVars[3] & 0x7F);
    Message_StartAreaMessage(86);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    SND_PlayBGM(0xA, 0x64, 8);
}
