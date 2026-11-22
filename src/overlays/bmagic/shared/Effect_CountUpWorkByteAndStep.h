/* Counts the work byte 0x04 up by two and steps the handler when it
 * reaches 16.
 */
/* func_801EF2D4, func_801EF1A0 */
MATCH void Effect_CountUpWorkByteAndStep(void) {
    u8 timer;

    timer               = BMAGIC_WORK->unk_04 + 2;
    BMAGIC_WORK->unk_04 = timer;
    if (timer == 16) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
    }
}
