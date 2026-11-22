/* Raises the ticker and timer, lowers the counter by two and advances the step when it reaches 0x10. */
/* func_801EF09C (magic055), func_801EF09C (magic091) */
MATCH void func_801EF09C(void) {
    u8 counter;

    BMAGIC_WORK->param.unk_0B += 1;
    BMAGIC_WORK->timer += 2;
    counter             = BMAGIC_WORK->unk_09 - 2;
    BMAGIC_WORK->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x10) {
        BMAGIC_WORK->header.mode += 1;
    }
}
