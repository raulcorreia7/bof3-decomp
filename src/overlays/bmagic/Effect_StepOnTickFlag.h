/* Advances the effect step (work byte 0x02) while bit 0x80 of the other
 * battler's effect ticker (work byte 0x0B of g_BattleEffectBattler) is set. One definition
 * shared by the bmagic effect modules; every change here must verify every member. */
/* func_801F03DC (magic092), func_801F00F0 (magic144) */
MATCH void Effect_StepOnTickFlag(void) {
    PartyBattler* work;

    work = (PartyBattler*)g_BattleEffectBattler;
    if ((work->param.unk_0B & 0x80) != 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
