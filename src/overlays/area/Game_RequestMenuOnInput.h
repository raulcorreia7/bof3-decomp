/* Requests the menu and clears the actor state when the menu pad mask is
 * pressed and the run lock is off, playing the menu cue; reports whether it
 * fired.
 */
/* func_801F5034 (area104), func_801F5578 (area121) */
MATCH s32 Game_RequestMenuOnInput(void) {
    if ((g_InputPressed & D_80145AB8) == 0) {
        return 0;
    }
    if (g_GameFlags & GAME_FLAG_RUN_LOCK) {
        return 0;
    }
    SND_PlayCue(EMI_CUE_ID(1, 5));
    g_GameStateIndex = GAME_REQUEST_MENU;
    ACTOR_CLEAR_STATE();
    return 1;
}
