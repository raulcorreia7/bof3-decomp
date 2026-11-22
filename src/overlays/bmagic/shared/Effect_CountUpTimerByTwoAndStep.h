/* Counts the timer at byte 0x0A up by two and steps the handler when it
 * reaches 16.
 */
/* func_801EF0E8, func_801EF38C */
MATCH void Effect_CountUpTimerByTwoAndStep(void) {
    BMAGIC_WORK->timer += 2;
    if (BMAGIC_WORK->timer == 16) {
        BMAGIC_WORK->header.step += 1;
    }
}
