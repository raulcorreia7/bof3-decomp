/* Advances the step while the effect's own ticker flag 0x80 is set. Every change here must verify every member. */
/* func_801EF350 (magic092), func_801EF11C (magic144) */
MATCH void Effect_StepOnOwnTickFlag(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B & 0x80) {
        work->unk_02++;
    }
}
