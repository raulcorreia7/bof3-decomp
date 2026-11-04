/* Counts the effect timer (work byte 0x09) down; at zero it runs two calls on
 * the selected battler, loads the effect counter (0x0A) from the second, reloads
 * the timer with 8 and advances the step byte (0x01). One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
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
