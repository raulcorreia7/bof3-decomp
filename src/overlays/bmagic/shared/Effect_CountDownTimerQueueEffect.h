/* Counts the timer down; at zero queues the selection sound and advances the step. */
/* func_801EEDB0 (magic048), func_801EEE20 (magic222) */
MATCH void Effect_CountDownTimerQueueEffect(void) {
    PartyMember* work;

    work         = SELF(PartyMember);
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_SEQueueSelection(0x100);
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}
