#include "area175_13.h"

MATCH void func_801F439C(void) {
    u8* bank;
    u8* table;
    u8* row;

    bank  = g_AreaLoads[g_GameAreaId];
    table = FIELD(u8*, bank, 0x10);
    row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
    row += g_ScriptState->cursor;
    Message_StartAreaMessage(D_801F5388[row[2]]);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_ScriptState->flag_00 &= ~0x10;
    g_ScriptState->flag_00 |= 0x20;
    g_ScriptState->cursor++;
}
