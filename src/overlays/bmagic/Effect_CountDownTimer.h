/* Counts the effect timer down and finishes the effect at zero. One definition
 * shared by the bmagic effect modules; each image header sets EFFECT_TIMER_STEP.
 * Every change here must verify every member. */
/* func_801EF0A0 (magic145), func_801EF1D0 (magic040), func_801EF340 (magic009), func_801EF5C0 (magic059), func_801EF6E0 (magic039), func_801EFCE4 (magic126), func_801F0290 (magic006) */
MATCH void Effect_CountDownTimer(void) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_SpadWork;
    work->word_08.byte.unk_09 += EFFECT_TIMER_STEP;
    work                      = g_SpadWork;
    count                     = work->word_08.byte.unk_0A - 1;
    work->word_08.byte.unk_0A = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B--;
        func_801E5988();
    }
}
