/* Advance the work-area timer; once it reaches 8, step the origin counter and keep counting. */
/* func_801F3568 */
MATCH void Actor_AdvanceTimer(void) {
    Actor* work;

    work = g_Task;
    if (work->timer >= 8) {
        work->header.step++;
    }
    work = g_Task;
    work->timer++;
}
