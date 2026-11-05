#include "area174_13.h"

MATCH void func_801F49C8(void) {
    u8* bank;
    u8* table;
    u8* row;
    u8  step;

    bank  = g_AreaLoads[g_GameAreaId];
    table = FIELD(u8*, bank, 0x10);
    row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
    row += g_ScriptState->cursor;
    step = row[2];
    func_801F4A5C(D_801F6748[step], D_80145E98 ^ 4);
    g_ScriptState->cursor++;
}
