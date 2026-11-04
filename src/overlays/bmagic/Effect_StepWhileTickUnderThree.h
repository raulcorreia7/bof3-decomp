/* Advances the effect step (work byte 0x02) while the other battler's effect
 * ticker (work byte 0x0B of D_801EB4E0) is under 3. One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* func_801EF5D8 (magic062), func_801EF680 (magic082), func_801EF8F8 (magic110), func_801EF888 (magic220) */
MATCH void Effect_StepWhileTickUnderThree(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    if (work->word_08.byte.unk_0B < 3) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
