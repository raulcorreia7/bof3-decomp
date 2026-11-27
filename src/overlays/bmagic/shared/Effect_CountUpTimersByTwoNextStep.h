/* Counts the timer and the wait up by two; advances the step at timer 0x10. */
/* func_801EF2D4 (magic009), func_801EF034 (magic145), func_801EF520 (magic146) */
MATCH void Effect_CountUpTimersByTwoNextStep(void) {
    SELF(PartyMember)->unk_09 += 2;
    SELF(PartyMember)->timer += 2;
    if (SELF(PartyMember)->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}
