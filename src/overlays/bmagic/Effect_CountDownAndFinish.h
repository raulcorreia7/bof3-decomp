/* Counts the wait down and finishes the effect at zero. Every change here must verify every member. */
/* func_801EF3E0 (magic096), func_801EF478 (magic130) */
MATCH void Effect_CountDownAndFinish(void) {
    PartyMember* work;

    work        = g_Task;
    work->timer = work->timer - 1;
    if (work->timer == 0) {
        work               = BATTLE_ACTIVE_WORK;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}
