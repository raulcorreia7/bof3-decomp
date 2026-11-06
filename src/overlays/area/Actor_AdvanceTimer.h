/* Advance the work-area timer; once it reaches 8, step the origin counter and
 * keep counting. One definition shared by the world area overlays; every
 * change here must verify every member address. */
/* func_801F3568 */
MATCH void Actor_AdvanceTimer(void) {
    Actor* work;

    work = g_Task;
    if (work->unk_09 >= 8) {
        work->header.step++;
    }
    work = g_Task;
    work->unk_09++;
}
