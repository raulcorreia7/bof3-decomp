/* Runs the step handler that the work byte at +1 of the bmagic effect work
 * array D_801F17B4 selects from D_801F01B0. One definition shared by the
 * bmagic overlays; every change here must verify every member. */
/* func_801EF33C (magic070), func_801EF33C (magic071), func_801EF33C (magic072) */
MATCH void func_801EF33C(void) {
    BmagicEffectWork* work;

    work = D_801F17B4;
    D_801F01B0[work->step_01]();
}
