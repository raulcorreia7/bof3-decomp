/* Advances the effect step (work byte 0x02) while bit 0x80 of the other
 * battler's effect ticker (work byte 0x0B of D_801EB4E0) is set. One definition
 * shared by the bmagic effect modules; every change here must verify every member. */
/* func_801F03DC (magic092), func_801F00F0 (magic144) */
MATCH void Effect_StepOnTickFlag(void) {
    PartyBattler* work;

    work = (PartyBattler*)D_801EB4E0;
    if ((work->word_08.byte.unk_0B & 0x80) != 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
