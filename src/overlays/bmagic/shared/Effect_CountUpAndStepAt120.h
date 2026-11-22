/* Counts the timer up and advances the step at 120. */
/* func_801EF374 (magic120), func_801EF24C (magic122) */
MATCH void Effect_CountUpAndStepAt120(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 120) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}
