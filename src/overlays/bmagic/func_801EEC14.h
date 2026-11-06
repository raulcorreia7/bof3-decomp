/* Runs the handler that the active battler's mode selects from the module head's table.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEC14 (magic010), func_801EEC14 (magic102), func_801EEC14 (magic104), func_801EEC14 (magic109), func_801EEC14
   (magic115), func_801EEC14 (magic116) */
MATCH void func_801EEC14(void) {
    BattleHandlerTable4 handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.handlers, 1, g_Task);
}
