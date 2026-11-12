#include "area174_13.h"

MATCH void func_801F4810(void) {
    u8* bank;
    u8* table;
    u8* row;
    u8* current;

    bank  = g_AreaLoads[g_GameAreaId];
    table = FIELD(u8*, bank, 0x10);
    row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
    if (g_Task->direction_08 != row[g_ScriptState->cursor + 2]) {
        g_Task->direction_08 = (g_Task->direction_08 + 1) & 7;
        current              = row + g_ScriptState->cursor;
        func_801F4A5C(D_801F6748[current[3]], g_Task->direction_08);
        g_ScriptState->cursor -= 2;
    } else {
        g_ScriptState->cursor += 2;
    }
}
