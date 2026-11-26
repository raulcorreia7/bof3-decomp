/* Counts the work byte 0x04 up by two and steps the handler when it
 * reaches 16.
 */
/* func_801EF2D4, func_801EF1A0 */
MATCH void Effect_CountUpWorkByteAndStep(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_04 + 2;
    SELF(PartyMember)->unk_04 = timer;
    if (timer == 16) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
