/* Scrolls the actor screen origin down by 0x10 and cues 0x201 when it reaches
 * zero. Like Actor_SlideScreenDown but with half the step. One definition
 * shared by the world area overlays; every change here must verify every
 * member.
 */
/* func_801F314C (area167), func_801F38A4 (area168), func_801F3078 (area169), func_801F4080 (area170), func_801F4570 (area173), func_801F38E8 (area174) */
MATCH void Actor_SlideScreenDown16(void) {
    Actor* work;

    work = g_SpadWork;
    work->unk_30 -= 0x10;
    if ((s16)work->unk_30 <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(2, 1));
        }
        g_SpadWork->state_02 = 1;
    }
    Area_Update();
}
