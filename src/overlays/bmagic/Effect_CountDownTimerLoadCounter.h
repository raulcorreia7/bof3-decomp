/* Counts the timer down; at zero loads the wait from the selected battler and advances the step. Every change here must verify every member. */
/* func_801EEEC0 (magic062), func_801EEF0C (magic082) */
MATCH void Effect_CountDownTimerLoadCounter(void) {
    PartyBattler* battler;
    u8            value;

    battler                         = g_BattleSelectedActor;
    value                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = value;
    if (!(value & 0xFF)) {
        func_80196718(battler);
        g_SpadWork->word_08.byte.timer_0A = func_8019651C(battler, 0, 0, 0, 1);
        g_SpadWork->word_08.byte.unk_09   = 8;
        g_SpadWork->step_01 += 1;
    }
}
