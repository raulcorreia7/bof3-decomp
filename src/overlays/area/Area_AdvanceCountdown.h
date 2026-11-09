/* Advances the countdown at g_Task +0x30 by 0x10: when it reaches zero or below the state byte moves to 1 and, if g_GameStateIndex is 0, cue 0x201 plays; the frame update then runs with the mode taken from the sign of g_Task +0x32. Members keep the explicit Actor view because not every member unit defines the view macro. */
/* func_801F311C (area148/13), func_801F30AC (area147/13) */
MATCH void Area_AdvanceCountdown(void) {
    u16 count;

    count              = (g_Task)->screen_y - 0x10;
    (g_Task)->screen_y = count;
    if ((s16)count <= 0) {
        if (g_GameStateIndex == GAME_REQUEST_IDLE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x01));
        }
        (g_Task)->header.step = 1;
    }
    if ((s16)(g_Task)->unk_32 != 0) {
        Area_Update(0);
    } else {
        Area_Update(-1);
    }
}
