/* Dispatches spad-work task 1 through the module head's five-handler table.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEC18 (magic068), func_801EEC18 (magic099), func_801EEC18 (magic132) */
MATCH void func_801EEC18(void) {
    Magic068SharedSteps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}
