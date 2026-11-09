/* Dispatches spad-work task 1 through the module head's ring table. */
/* func_801EEC24 (magic065), func_801EEC24 (magic117), func_801EEC24 (magic154) */
MATCH void func_801EEC24(void) {
    Magic065SharedSteps table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}
