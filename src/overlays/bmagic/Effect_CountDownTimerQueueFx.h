/* Counts the timer down; at zero queues the selection sound and advances the step. Every change here must verify every member. */
/* func_801EEDB0 (magic048), func_801EEE20 (magic222) */
MATCH void Effect_CountDownTimerQueueFx(void) {
    PartyBattler* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_QueueSelectionFx(0x100);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
