#include "area008_13.h"

MATCH void func_801F437C(void) {
    TEXT_Format(g_TextVariables[0], D_801F2C14, g_ScriptVars[3] & 0x7F);
    Message_StartAreaMessage(84);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}
