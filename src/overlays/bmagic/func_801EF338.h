/* Runs the step handler that the work byte at +1 of the bmagic effect work array D_801F17B0 selects from D_801F01AC. */
/* func_801EF338 (magic162), func_801EF338 (magic168) */
MATCH void func_801EF338(void) {
    BMagicEffect* work;

    work = D_801F17B0;
    D_801F01AC[work->header.mode]();
}
