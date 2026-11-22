MATCH void Effect_AdvanceOnTick(void) {
    TASK(PartyMember)->unk_09 += EFFECT_TICK_INCREMENT;
    if (TASK(PartyMember)->unk_09 == EFFECT_TICK_LIMIT) {
        TASK(PartyMember)->header.mode += 1;
    }
}
