/* Runs the step handler that the work byte at +1 of the bmagic effect work array D_801F17B4 selects from D_801F01B0. */
/* func_801EF33C (magic070), func_801EF33C (magic071), func_801EF33C (magic072) */
MATCH void func_801EF33C(void) {
    BMagicEffect* work;

    work = D_801F17B4;
    D_801F01B0[work->header.mode]();
}
