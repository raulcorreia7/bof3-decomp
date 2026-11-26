/* Clears the trail and finishes the effect when the timer expires. */
/* func_801EF478 (magic044), func_801EF484 (magic173) */
MATCH void Effect_EndTrail(void) {
    u8 timer;

    Effect_ClearTrail();
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        Effect_Reset();
    }
}
