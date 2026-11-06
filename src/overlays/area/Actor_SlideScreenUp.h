/* Scrolls the actor screen origin up by 0x20 and cues 0x201 when it reaches
 * zero. One definition shared by the world04 area overlays; every change here
 * must verify every member. */
/* func_801F3064 */
MATCH void Actor_SlideScreenUp(void) {
    Actor* work;

    work = g_Task;
    work->unk_30 += 0x20;
    if ((s16)work->unk_30 >= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        g_Task->header.step = 1;
    }
    Area_Update();
}
