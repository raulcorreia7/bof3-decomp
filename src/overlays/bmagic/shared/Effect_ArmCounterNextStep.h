/* Starts a 0x88-frame wait and advances the step. */
/* func_801EFF8C (magic067), func_801EFCC0 (magic137), func_801EF0B8 (magic223) */
MATCH void Effect_ArmCounterNextStep(void) {
    g_Task->unk_09 = 0;
    g_Task->timer  = 136;
    BMagic_NextStep();
}
