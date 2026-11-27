MATCH void Effect_AdvanceOnTick(void) {
    SELF(PartyMember)->unk_09 += EFFECT_TICK_INCREMENT;
    if (SELF(PartyMember)->unk_09 == EFFECT_TICK_LIMIT) {
        SELF(PartyMember)->header.mode += 1;
    }
}
