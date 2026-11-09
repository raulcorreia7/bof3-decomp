#include "area174_13.h"

MATCH void func_801F41A8(void) {
    u8* bank;
    u8* table;
    u8* row;
    u16 pc;
    u8  frame;
    u8  mirror;

    pc = g_Task->script_pc;
    if (pc == 2) {
        bank   = g_AreaLoads[g_GameAreaId];
        table  = FIELD(u8*, bank, 0x10);
        row    = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
        row += g_ScriptState->cursor;
        frame  = row[2];
        mirror = row[3];
        Actor_BeginScript(frame, pc - 2);
        g_Task->unk_2A = mirror;
        g_ScriptState->cursor += 2;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
