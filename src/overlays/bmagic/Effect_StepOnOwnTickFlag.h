/* Advances the effect step (work byte 0x02) while bit 0x80 of the effect
 * ticker (work byte 0x0B) is set; Effect_StepOnTickFlag reads the other
 * battler's ticker instead. One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EF350 (magic092), func_801EF11C (magic144) */
MATCH void Effect_StepOnOwnTickFlag(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B & 0x80) {
        work->unk_02++;
    }
}
