/* Counts the timer at byte 0x0A up by two and steps the handler when it
 * reaches 16.
 */
/* func_801EF0E8, func_801EF38C */
MATCH void Effect_CountUpTimerByTwoAndStep(void) {
    SELF(PartyMember)->timer += 2;
    if (SELF(PartyMember)->timer == 16) {
        SELF(PartyMember)->header.step += 1;
    }
}
