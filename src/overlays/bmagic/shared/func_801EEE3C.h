/* Advances the effect counters and moves to the next step when the first reaches 0x10. */
/* func_801EEE3C (magic055), func_801EEE3C (magic091) */
MATCH void func_801EEE3C(void) {
    BMAGIC_WORK->unk_09 += 1;
    BMAGIC_WORK->timer += 1;
    if (BMAGIC_WORK->unk_09 == 0x10) {
        BMAGIC_WORK->header.mode = BMAGIC_WORK->header.mode + 1;
    }
}
