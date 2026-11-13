/* Runs the area script row under the script cursor when the row's step byte differs from the actor's
 * facing: turns the actor to the given direction, calls that step's handler and rewinds the cursor; otherwise
 * it skips the row. The member declares `u8* bank`, `u8* table` and `u8* row`.
 * Members: area174/13 func_801F4810 and func_801F48EC. */
#define ACTOR_RUN_SCRIPT_ROW_STEP(NEXT_DIRECTION)                                                   \
    bank  = g_AreaLoads[g_GameAreaId];                                                              \
    table = FIELD(u8*, bank, 0x10);                                                                 \
    row   = FIELD(u8*, table, g_ScriptState->pad_03 * 4);                                           \
    if (g_Task->direction_08 != row[g_ScriptState->cursor + 2]) {                                   \
        g_Task->direction_08 = (NEXT_DIRECTION) & 7;                                                \
        func_801F4A5C(D_801F6748[FIELD(u8, row, g_ScriptState->cursor + 3)], g_Task->direction_08); \
        g_ScriptState->cursor -= 2;                                                                 \
    } else {                                                                                        \
        g_ScriptState->cursor += 2;                                                                 \
    }
