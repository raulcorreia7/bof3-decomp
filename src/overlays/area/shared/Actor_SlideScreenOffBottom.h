/* Scrolls the actor screen origin down by 0x20 and advances the state when it passes the image edge. */
/* func_801F2EF8 */
MATCH void Actor_SlideScreenOffBottom(void) {
    Actor* work;

    work = SELF(Actor);
    work->screen_y -= 0x20;
    if (work->screen_y < -0xFF) {
        work->header.step++;
    }
    Area_Update();
}
