/* Advances the effect step (work byte 0x02) while the other battler's effect
 * ticker (work byte 0x0B of D_801EB4E0) is under 2. One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
/* func_801EFBA8 (magic004), func_801EF5EC (magic088), func_801EF078 (magic126), func_801EF410 (magic167), func_801EF148 (magic223) */
MATCH void Effect_StepWhileTickUnderTwo(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    if (work->word_08.byte.unk_0B < 2) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
