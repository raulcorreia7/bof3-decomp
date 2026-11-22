/* Counts the ticker down and advances the step at zero. */
/* func_801EF8A0 (magic086), func_801EF348 (magic096) */
MATCH void Effect_CountDownTickerAndStep(void) {
    u8 timer;

    timer                     = BMAGIC_WORK->param.unk_0B - 1;
    BMAGIC_WORK->param.unk_0B = timer;
    if (timer == 0) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
    }
}
