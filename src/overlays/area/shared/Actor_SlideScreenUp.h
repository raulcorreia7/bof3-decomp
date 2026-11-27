/* Scrolls the actor screen origin up by 0x20 and SEs 0x201 when it reaches zero. */
/* func_801F3064 (area158, area161, area162, area166), func_801F3F14 (area139) */
MATCH void Actor_SlideScreenUp(void) {
    Actor* work;

    work = SELF(Actor);
    work->screen_y += 0x20;
    if (work->screen_y >= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 1));
        }
        SELF(Actor)->header.step = 1;
    }
    Area_Update();
}
