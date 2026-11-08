/* Dispatches the stored handler in slot 2 of the effect handler table for
 * the work battler.
 */
/* func_801EF1F0, func_801EFFBC */
MATCH void Effect_DispatchStep(void) {
    EffectDispatchSteps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}
