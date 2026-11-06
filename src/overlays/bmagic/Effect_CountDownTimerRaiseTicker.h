/* Raises the ticker and counts the timer down; at zero advances the step. Every change here must verify every member. */
/* func_801EF3E4 (magic099), func_801F1318 (magic151) */
MATCH void Effect_CountDownTimerRaiseTicker(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_0B++;
    work = g_Task;
    work->unk_09--;
    if (work->unk_09 == 0) {
        work = g_Task;
        work->header.step++;
    }
}
