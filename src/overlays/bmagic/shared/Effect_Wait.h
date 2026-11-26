/* Raises the ticker and counts the timer down; at zero advances the step. */
/* func_801EF3E4 (magic099), func_801F1318 (magic151) */
MATCH void Effect_Wait(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->param.unk_0B++;
    work = SELF(PartyMember);
    work->unk_09--;
    if (work->unk_09 == 0) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}
