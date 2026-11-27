/* Counts the timer up and advances the step at 30. */
/* func_801EFBA4 (magic056), func_801F0410 (magic103) */
MATCH void Effect_CountUpAndStepAt30(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 30) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
