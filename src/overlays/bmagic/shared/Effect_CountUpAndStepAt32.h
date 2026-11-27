/* Counts the timer up and advances the step at 32. */
/* func_801EF180 (magic040), func_801EF9DC (magic088) */
MATCH void Effect_CountUpAndStepAt32(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 32) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
