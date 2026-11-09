/* Shrinks the actor scale by 0x2000 and finishes or resets the area when the
 * timer expires. One definition shared by the two world area overlays; every
 * change here must verify every member. */
/* func_801F3360 , func_801F3294 (area033), func_801F32D0 (area151), func_801F3394 (area087), func_801F3398 (area065),
   func_801F3424 (area104), func_801F3EC4 (area088) */
MATCH void Actor_ZoomOut(void) {
    Actor* scratch;
    Actor* check;

    Actor_CenterOnScreen();

    scratch = g_Task;
    scratch->timer -= 1;

    check = g_Task;
    scratch->scale.x -= 0x2000;

    if (check->timer == 0) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Actor_Clear();
            return;
        }
        check->unk_48       = 0;
        g_Task->header.mode = 1;
        return;
    }

    Area_AddActor();
}
