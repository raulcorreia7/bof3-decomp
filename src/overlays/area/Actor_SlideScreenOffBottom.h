/* Scrolls the actor screen origin down by 0x20 and advances the state when it
 * passes the image edge. One definition shared by the world04 area overlays;
 * every change here must verify every member. */
/* func_801F2EF8 */
MATCH void Actor_SlideScreenOffBottom(void) {
    Actor* work;

    work = g_Task;
    work->unk_30 -= 0x20;
    if ((s16)work->unk_30 < -0xFF) {
        work->step++;
    }
    Area_Update();
}
