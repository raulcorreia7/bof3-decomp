#include "commu00_00.h"

MATCH s32 func_801F13B8(void) {
    char* dest;
    char* fmt;

    dest = (char*)g_TextVariables;
    fmt  = D_801EEC44;
    TEXT_Format(dest, fmt, D_80145034);
    TEXT_Format(dest + 0x20, fmt, D_80145038);
    TEXT_Format(dest + 0x40, fmt, D_8014503C);
    Message_StartAreaMessage(FAIRY_MESSAGE_PLAY_RECORD_COUNTS);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    return 0;
}
