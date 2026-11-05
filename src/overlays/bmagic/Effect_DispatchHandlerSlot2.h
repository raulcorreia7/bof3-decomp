/* Dispatches the stored handler in slot 2 of the effect handler table for
 * the work battler.
 */
/* func_801EF1F0, func_801EFFBC */
MATCH void Effect_DispatchHandlerSlot2(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.handlers, 2, g_SpadWork);
}
