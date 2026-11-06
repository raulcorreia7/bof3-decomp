/* Runs the step handler that the spad-work mode byte selects from the
 * module head's six-handler table. One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEC38 (magic041), func_801EEC48 (magic020), func_801EEC1C (magic062, magic082, magic086, magic110, magic167)
*/
MATCH void Effect_DispatchHandlerSlot1(void) {
    BmagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.mode);
}
