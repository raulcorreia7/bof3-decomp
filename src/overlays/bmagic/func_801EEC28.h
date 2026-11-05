/* Dispatches spad-work task 1 through the module head's five-handler table.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEC28 (magic004), func_801EEC28 (magic009) */
MATCH void func_801EEC28(void) {
    BattleHandlerTable5 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_Task);
}
