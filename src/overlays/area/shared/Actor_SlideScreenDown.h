/* Scrolls the actor screen origin down by 0x20 and SEs 0x201 when it reaches zero. */
/* func_801F3064 */
/* func_801F3098 (area157) */
MATCH void Actor_SlideScreenDown(void) {
    Actor* work;

    work = SELF(Actor);
    work->screen_y -= 0x20;
    if (work->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        SELF(Actor)->header.step = 1;
    }
    Area_Update();
}
