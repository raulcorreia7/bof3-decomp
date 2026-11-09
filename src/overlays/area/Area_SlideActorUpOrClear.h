/* Shrinks the actor's horizontal scale by 8192 fixed-point units per frame
 * while counting the timer down; at zero it releases the actor during an area
 * change, else clears the reset flag and moves the handler to mode 1.
 */
/* func_801F3364 (area115), func_801F3378 (area121) */
MATCH void Area_SlideActorUpOrClear(void) {
    Actor* work;
    Actor* check;

    Actor_CenterOnScreen();

    work = g_Task;
    work->timer -= 1;
    check = g_Task;
    work->scale.x -= 8192;

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
