/* Counts the ticker down and advances the step at zero. */
/* func_801EF8A0 (magic086), func_801EF348 (magic096) */
MATCH void Effect_CountDownTickerAndStep(void) {
    u8 timer;

    timer                           = SELF(PartyMember)->param.unk_0B - 1;
    SELF(PartyMember)->param.unk_0B = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}
