/* Scrolls the actor screen origin to y 240 and advances its state. */
/* func_801F3594 (area152), func_801F3604 (area033), func_801F3640 (area151), func_801F36D0 (area016), func_801F36D0
   (area045), func_801F36D4 (area115), func_801F36E8 (area121), func_801F3704 (area087), func_801F3708 (area065),
   func_801F3794 (area104), func_801F4234 (area088) */
MATCH void Actor_SetScreenBottom(void) {
    Actor* work;

    if (D_801454F2 == 0 || g_Task->param.unk_0B == 0) {
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
            work           = g_Task;
            work->screen_y = 240;
            work->unk_03++;
        }
    }
}
