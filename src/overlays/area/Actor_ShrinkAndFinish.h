/* Shrinks the actor scale by 0x2000 and finishes or resets the area when the
 * timer expires. One definition shared by the two world area overlays; every
 * change here must verify every member. */
/*  func_801F3360 , func_801F3294 (area033), func_801F32D0 (area151), func_801F3394 (area087), func_801F3398 (area065), func_801F3424 (area104), func_801F3EC4 (area088) */
MATCH void Actor_ShrinkAndFinish(void) {
    u8*  scratch;
    u8*  check;
    u8** slots;

    Actor_CenterOnScreen();

    slots   = SP_PTR(u8*, 0u);
    scratch = slots[0x11];
    scratch[0x09] -= 1;

    slots = SP_PTR(u8*, 0u);
    check = slots[0x11];
    *(s32*)(scratch + 0x40) -= 0x2000;

    if (check[0x09] == 0) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Actor_Clear();
            return;
        }
        check[0x48]              = 0;
        SP_PTR(u8*, 0u)[0x11][1] = 1;
        return;
    }

    Area_AddActor();
}
