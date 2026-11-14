/* Counts the timer down; at zero queues the selection sound and advances the step. */
/* func_801EEDB0 (magic048), func_801EEE20 (magic222) */
MATCH void Effect_CountDownTimerQueueEffect(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_QueueSelectionEffect(0x100);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
