/* Counts the timer up and advances the step at 32. */
/* func_801EF180 (magic040), func_801EF9DC (magic088) */
MATCH void Effect_CountUpAndStepAt32(void) {
    u8 timer;

    timer               = BMAGIC_WORK->unk_09 + 1;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 32) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
    }
}
