MATCH void Effect_AdvanceOnTick(void) {
    g_Task->word_08.byte.unk_09 += EFFECT_TICK_INCREMENT;
    if (g_Task->word_08.byte.unk_09 == EFFECT_TICK_LIMIT) {
        g_Task->mode += 1;
    }
}
