/* Counts the effect timer (work byte 0x09) down by two. */
/* func_801F0650 (magic126), func_801EF770 (magic172) */
MATCH void Effect_TickOnTimerNegative(void) {
    PartyMember* work;
    s8           timer;

    work         = g_Task;
    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    if (timer < 0) {
        work               = g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}
