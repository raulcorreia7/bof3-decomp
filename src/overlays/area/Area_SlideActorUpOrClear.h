/* Slides the actor up its screen coordinate by 0x2000 fixed-point units
 * per frame while counting byte 0x09 down; at zero it releases the actor
 * during an area change, else clears byte 0x48 and moves the handler to
 * state 1.
 */
/* func_801F3364 (area115), func_801F3378 (area121) */
MATCH void Area_SlideActorUpOrClear(void) {
    u8* work;
    u8* check;

    Actor_CenterOnScreen();

    work = (u8*)g_SpadWork;
    work[9] -= 1;
    check = (u8*)g_SpadWork;
    FIELD(s32, work, 0x40) -= 0x2000;

    if (check[9] == 0) {
        if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
            Actor_Clear();
            return;
        }
        check[0x48]        = 0;
        g_SpadWork->unk_01 = 1;
        return;
    }

    Area_AddActor();
}
