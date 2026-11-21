/* Clear the effect timer and advance the effect step. */
/* func_801F0000 (magic060), func_801F0DA8 (magic064), func_801F0178 (magic131) */
MATCH void Effect_ClearTimerNextStep(void) {
    g_Task->unk_09 = 0;
    BMagic_NextStep();
}
