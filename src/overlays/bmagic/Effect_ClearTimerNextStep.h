/* Clear the effect timer and advance the effect step. One definition shared by
 * the bmagic overlays; every change here must verify every member. */
/* func_801F0000 (magic060), func_801F0DA8 (magic064), func_801F0178 (magic131) */
MATCH void Effect_ClearTimerNextStep(void) {
    g_SpadWork->unk_09 = 0;
    Bmagic_NextStep();
}
