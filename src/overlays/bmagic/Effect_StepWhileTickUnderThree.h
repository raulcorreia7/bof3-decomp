/* Advances the effect step (work byte 0x02) while the other battler's effect
 * ticker (work byte 0x0B of g_BattleEffectBattler) is under 3. One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* func_801EF5D8 (magic062), func_801EF680 (magic082), func_801EF8F8 (magic110), func_801EF888 (magic220) */
MATCH void Effect_StepWhileTickUnderThree(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_BattleEffectBattler;
    if (work->param.unk_0B < 3) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
