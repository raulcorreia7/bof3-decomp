/* Counts the timer up and advances the step at 32. */
/* func_801EF180 (magic040), func_801EF9DC (magic088) */
MATCH void Effect_CountUpAndStepAt32(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 32) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}
