/* Scrolls the actor screen origin down by 0x20 and cues 0x201 when it reaches
 * zero. One definition shared by the world04 area overlays; every change here
 * must verify every member. */
/* func_801F3064 */
/* func_801F3098 (area157) */
MATCH void Actor_SlideScreenDown(void) {
    Actor* work;

    work = g_Task;
    work->screen_y -= 0x20;
    if ((s16)work->screen_y <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
        }
        g_Task->header.step = 1;
    }
    Area_Update();
}
