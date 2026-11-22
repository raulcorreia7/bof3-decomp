MATCH void Effect_AdvanceOnTick(void) {
    BMAGIC_WORK->unk_09 += EFFECT_TICK_INCREMENT;
    if (BMAGIC_WORK->unk_09 == EFFECT_TICK_LIMIT) {
        BMAGIC_WORK->header.mode += 1;
    }
}
