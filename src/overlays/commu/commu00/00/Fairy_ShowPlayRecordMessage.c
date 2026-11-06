#include "commu00_00.h"

MATCH s32 Fairy_ShowPlayRecordMessage(void) {
    char* dest;
    char* fmt;

    dest = (char*)g_TextVariables;
    fmt  = D_801EEC44;
    sprintf(dest, fmt, g_SaveData.play_clock.hours_00);
    sprintf(dest + 0x20, fmt, g_SaveData.play_clock.minutes_01);
    sprintf(dest + 0x40, fmt, g_SaveData.battle_count);
    sprintf(dest + 0x60, fmt, D_80145030);
    Message_StartAreaMessage(0x55);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    return 0;
}
