/* Sets the three screen shake offsets from the effect ticker and counts the
 * effect down. One definition shared by the battle and boss overlays; every
 * change here must verify every member. */
/* func_800A8EB8 (battle), func_800C26A4 (boss033) */
MATCH void Effect_ShakeScreen(void) {
    {
        PartyBattler* work;

        work         = (PartyBattler*)g_SpadWork;
        work->unk_5D = -(work->word_08.byte.unk_0B * 16);
        work         = (PartyBattler*)g_SpadWork;
        work->unk_5F = -(work->word_08.byte.unk_0B * 16);
        work         = (PartyBattler*)g_SpadWork;
        work->unk_5E = -(work->word_08.byte.unk_0B * 16);
    }
    func_8014DAEC();
    {
        PartyBattler* work;
        u8            old;

        work                      = (PartyBattler*)g_SpadWork;
        old                       = work->word_08.byte.unk_09;
        work->word_08.byte.unk_09 = old + 255;
        if (old == 0) {
            func_801E5988();
        }
    }
}
