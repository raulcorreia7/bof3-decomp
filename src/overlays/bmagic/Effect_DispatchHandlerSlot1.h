/* Dispatches the stored handler in slot 1 of the effect handler table for
 * the work battler. The local copy of the table is part of the matched
 * bytes, so each table width keeps its own body.
 */
/* func_801EEC38, func_801EEC48 */
MATCH void Effect_DispatchHandlerSlot1(void) {
    BattleHandlerTable6 handlers = D_801EEC04;

    SYS_DISPATCH_TASK(handlers.handlers, 1, g_SpadWork);
}
