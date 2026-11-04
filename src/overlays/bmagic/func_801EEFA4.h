/* Counts the step byte down; at zero it runs the battler step, rearms the timer and advances step_01.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEFA4 (magic070), func_801EEFA4 (magic071) */
MATCH void func_801EEFA4(void) {
    PartyBattler* temp_s0;
    u8            temp_v0;

    temp_s0                         = g_BattleSelectedActor;
    temp_v0                         = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_80196718(temp_s0);
        g_SpadWork->word_08.byte.timer_0A = func_8019651C(temp_s0, 0, 0, 0, 1);
        g_SpadWork->word_08.byte.unk_09   = 8;
        g_SpadWork->step_01 += 1;
    }
}
