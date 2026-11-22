/* Counts the timer up and advances the step at 30. */
/* func_801EFBA4 (magic056), func_801F0410 (magic103) */
MATCH void Effect_CountUpAndStepAt30(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 30) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}
