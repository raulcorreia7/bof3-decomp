/* Slides the actor screen origin by 0x10 and advances the step at 0x80. */
/* func_801F2F34 (area147) */
/* func_801F2FA4 (area148) */
MATCH void Actor_SlideScreenToEdge(void) {
    Actor* work;
    u16    screen_y;
    s16    v;

    work           = g_Task;
    screen_y       = work->screen_y + 0x10;
    work->screen_y = screen_y;
    if ((s16)screen_y >= 0x80) {
        g_Task->header.step += 1;
    }
    v = g_Task->unk_32;
    if (v != 0) {
        Area_Update(0);
    } else {
        Area_Update(-1);
    }
}
