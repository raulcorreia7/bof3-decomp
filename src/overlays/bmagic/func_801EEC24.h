/* Dispatches spad-work task 1 through the module head's ring table.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEC24 (magic065), func_801EEC24 (magic154) */
MATCH void func_801EEC24(void) {
    BattleResultRings table;

    table = D_801EEC04;
    SYS_DISPATCH_TASK(table.handlers, 1, g_Task);
}
