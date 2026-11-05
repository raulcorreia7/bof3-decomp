/* Counts the step byte down; at zero it runs the battler step, rearms the timer and advances step_01.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEFA4 (magic070), func_801EEFA4 (magic071) */
MATCH void func_801EEFA4(void) {
    PartyBattler* actor;
    u8            count;

    actor                           = g_BattleSelectedActor;
    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        func_80196718(actor);
        g_SpadWork->word_08.byte.timer_0A = func_8019651C(actor, 0, 0, 0, 1);
        g_SpadWork->word_08.byte.unk_09   = 8;
        g_SpadWork->step_01 += 1;
    }
}
