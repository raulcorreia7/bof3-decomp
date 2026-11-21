/* Scrolls the actor screen origin left by 0x30 and advances its state. */
/* func_801F33D0 (area152), func_801F3440 (area033), func_801F347C (area151), func_801F350C (area016), func_801F350C
   (area045), func_801F3510 (area115), func_801F3524 (area121), func_801F3540 (area087), func_801F3544 (area065),
   func_801F35D0 (area104), func_801F4070 (area088) */
MATCH void Actor_SlideScreenLeft(void) {
    Actor* work;
    s16    origin;

    if (D_801454F2 != 2 && GAME_SCRIPT_ACTIVE() == 0) {
        work           = g_Task;
        origin         = -0x30;
        work->screen_x = origin;
        work->header.step++;
    }
}
