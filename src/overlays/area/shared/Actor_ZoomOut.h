/* Shrinks the actor scale by 0x2000 and finishes or resets the area when the timer expires. */
/* func_801F3360 , func_801F3294 (area033), func_801F32D0 (area151), func_801F3394 (area087), func_801F3398 (area065),
   func_801F3424 (area104), func_801F3EC4 (area088) */
MATCH void Actor_ZoomOut(void) {
    Actor* scratch;
    Actor* check;

    Actor_SetScreenOrigin();

    scratch = SELF(Actor);
    scratch->timer -= 1;

    check = SELF(Actor);
    scratch->scale.x -= 0x2000;

    if (check->timer == 0) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Actor_Clear();
            return;
        }
        check->unk_48            = 0;
        SELF(Actor)->header.mode = 1;
        return;
    }

    Area_AddActor();
}
