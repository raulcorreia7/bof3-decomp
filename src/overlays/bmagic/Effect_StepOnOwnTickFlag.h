/* Advances the step while the effect's own ticker flag 0x80 is set. */
/* func_801EF350 (magic092), func_801EF11C (magic144) */
MATCH void Effect_StepOnOwnTickFlag(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B & 0x80) {
        work->header.step++;
    }
}
