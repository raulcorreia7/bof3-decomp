#include "commu00_00.h"

MATCH s32 Fairy_ShowPlayRecordMessage(void) {
    char* dest;
    char* fmt;

    dest = (char*)g_TextVariables;
    fmt  = D_801EEC44;
    sprintf(dest, fmt, g_PlayClock.hours_00);
    sprintf(dest + 0x20, fmt, g_PlayClock.minutes_01);
    sprintf(dest + 0x40, fmt, g_BattleCount);
    sprintf(dest + 0x60, fmt, D_80145030);
    Message_StartAreaMessage(0x55);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    return 0;
}
