/* Advances the effect step (work byte 0x02) while the other battler's effect
 * ticker (work byte 0x0B of g_BattleEffectBattler) is under 2. One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
/* func_801EFBA8 (magic004), func_801EF5EC (magic088), func_801EF078 (magic126), func_801EF410 (magic167), func_801EF148
   (magic223) */
MATCH void Effect_StepWhileTickUnderTwo(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_BattleEffectBattler;
    if (work->param.unk_0B < 2) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
