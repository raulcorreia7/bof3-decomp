MATCH void Effect_AdvanceOnTick(void) {
    g_Task->unk_09 += EFFECT_TICK_INCREMENT;
    if (g_Task->unk_09 == EFFECT_TICK_LIMIT) {
        g_Task->header.mode += 1;
    }
}
