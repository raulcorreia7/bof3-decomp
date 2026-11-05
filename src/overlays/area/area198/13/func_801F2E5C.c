#include "area198_13.h"

MATCH void func_801F2E5C(void) {
    u8* bank;
    u8* table;
    u8* row;
    u8  step;
    u8  arg;

    bank  = g_AreaLoads[g_GameAreaId];
    table = FIELD(u8*, bank, 0x10);
    row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
    row += g_ScriptState->cursor;
    step = row[2];
    arg  = row[3];
    Actor_BeginScript(step, g_SpadWork->script_pc - 2);
    g_SpadWork->unk_2A = arg;
    g_ScriptState->cursor += 2;
}
