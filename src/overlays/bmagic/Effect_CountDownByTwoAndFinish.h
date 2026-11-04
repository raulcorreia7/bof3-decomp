/* Counts the wait down by two and finishes the effect at zero. Every change here must verify every member. */
/* func_801EF488 (magic097), func_801EF498 (magic098), func_801EF100 (magic143), func_801F1380 (magic151) */
MATCH void Effect_CountDownByTwoAndFinish(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_0B   = g_SpadWork->word_08.byte.unk_0B + 1;
    g_SpadWork->word_08.byte.timer_0A = g_SpadWork->word_08.byte.timer_0A - 2;
    if (g_SpadWork->word_08.byte.timer_0A == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = active->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}
