/* Lowers the ticker and advances the step once Actor_StepAnimOnce reports ready. */
/* func_801EFA70 (magic004), func_801EF158 (magic161) */
MATCH void Effect_LowerTickerStepOnReady(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        g_Task->header.step++;
    }
}
