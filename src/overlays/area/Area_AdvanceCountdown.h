/* Advances the countdown at g_SpadWork +0x30 by 0x10: when it reaches zero or
 * below the state byte moves to 1 and, if g_GameStateIndex is 0, cue 0x201 plays;
 * the frame update then runs with the mode taken from the sign of g_SpadWork
 * +0x32. One definition shared by the world03 area overlays; members keep the
 * explicit Actor view because not every member unit defines the view macro.
 * Every change here must verify every member address.
 */
/* func_801F311C (area148/13), func_801F30AC (area147/13) */
MATCH void Area_AdvanceCountdown(void) {
    u16 count;

    count                        = ((Actor*)g_SpadWork)->unk_30 - 0x10;
    ((Actor*)g_SpadWork)->unk_30 = count;
    if ((s16)count <= 0) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x201U);
        }
        ((Actor*)g_SpadWork)->state_02 = 1;
    }
    if ((s16)((Actor*)g_SpadWork)->unk_32 != 0) {
        Area_Update(0);
    } else {
        Area_Update(-1);
    }
}
