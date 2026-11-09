/* Grows the actor's horizontal scale by 8192 fixed-point units per frame while
 * counting the timer down; at zero it clears the reset flag and moves the
 * handler to mode 3.
 */
/* func_801F3228 (area115), func_801F323C (area121) */
MATCH void Area_WidenActor(void) {
    Actor* work;
    Actor* reload;
    u8     timer;

    Actor_CenterOnScreen();

    work        = g_Task;
    timer       = work->timer;
    work->timer = timer - 1;
    reload      = g_Task;
    work->scale.x += 8192;

    if (reload->timer == 0) {
        reload->unk_48      = 0;
        g_Task->header.mode = 3;
    }

    Area_AddActor();
}
