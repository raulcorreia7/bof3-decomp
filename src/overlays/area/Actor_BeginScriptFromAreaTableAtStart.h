/* Starts the area script step at the cursor once the task script_pc is 2;
 * otherwise rewinds the cursor to repeat the command.
 */
/* func_801F41A8, func_801F2F04 */
MATCH void Actor_BeginScriptFromAreaTableAtStart(void) {
    u8* bank;
    u8* table;
    u8* row;
    u16 pc;
    u8  step;
    u8  arg;

    pc = g_Task->script_pc;
    if (pc == 2) {
        bank  = g_AreaLoads[g_GameAreaId];
        table = FIELD(u8*, bank, 0x10);
        row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);
        row += g_ScriptState->cursor;
        step = row[2];
        arg  = row[3];
        /* FAKE: retail reads Actor_BeginScript as void(u8, u16). */
        ((void (*)(u8, u16))Actor_BeginScript)(step, pc - 2);
        g_Task->unk_2A = arg;
        g_ScriptState->cursor += 2;
    } else {
        g_ScriptState->cursor -= 2;
    }
}
