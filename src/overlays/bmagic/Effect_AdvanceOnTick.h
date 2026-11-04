MATCH void Effect_AdvanceOnTick(void) {
    g_SpadWork->word_08.byte.unk_09 += EFFECT_TICK_INCREMENT;
    if (g_SpadWork->word_08.byte.unk_09 == EFFECT_TICK_LIMIT) {
        g_SpadWork->step_01 += 1;
    }
}
