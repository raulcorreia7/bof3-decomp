#include "commu00_00.h"

MATCH s32 Fairy_ShowPlayRecordMessage(void) {
    char* dest;
    char* fmt;

    dest = (char*)g_TextVariables;
    fmt  = D_801EEC44;
    TEXT_Format(dest, fmt, g_PlayClock.hours);
    TEXT_Format(dest + 0x20, fmt, g_PlayClock.minutes);
    TEXT_Format(dest + 0x40, fmt, g_BattleCount);
    TEXT_Format(dest + 0x60, fmt, D_80145030);
    Message_StartAreaMessage(FAIRY_MESSAGE_PLAY_RECORD);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    return 0;
}
