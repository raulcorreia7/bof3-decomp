/* Copy the module head's three state callbacks and run the one the shared spad
 * step byte selects. The callback triple is the proven MagicModule.steps
 * member, so the body takes no table parameter. One definition shared by the
 * bmagic effect modules; each includes this file where the function sits. */
/* func_801EEC10 (magic038), func_801EEC10 (magic048), func_801EEC10 (magic066), func_801EEC10 (magic075), func_801EEC10 (magic100), func_801EEC10 (magic103), func_801EEC10 (magic120), func_801EEC10 (magic130), func_801EEC10 (magic145), func_801EEC10 (magic216), func_801EEC10 (magic222), func_801EEC18 (magic002), func_801EEC1C (magic052), func_801EEC1C (magic111), func_801EEC1C (magic137), func_801EEC20 (magic040), func_801EEC24 (magic096), func_801EEC24 (magic161), func_801EEC28 (magic138), func_801EEC34 (magic039), func_801EEC34 (magic056), func_801EEC38 (magic017), func_801EEC50 (magic151), func_801EEC64 (magic001), BMagic_RunStep (magic050), BMagic_RunStep (magic057), BMagic_RunStep (magic064) */
MATCH void BMagic_RunStep(void) {
    BattleHandlerTable3 handlers;

    handlers = D_801EEC00.steps;
    handlers.handlers[g_SpadWork->step_01]();
}
