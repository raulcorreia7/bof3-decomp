/* Ends a turning step: begins the next one or stores the direction. */
/* func_801F58E8 (area104), func_801F5E2C (area121) */
MATCH void Area_EndTurn(void) {
    u8* heading;

    heading = &g_Game.members[0].facing;
    if (g_Task->direction != *heading) {
        if ((u8)Area_StartTurn(g_Task->direction, *heading) != 0) {
            return;
        }
        if ((u8)Area_StartTurn(g_Task->direction ^ 4, *heading) != 0) {
            return;
        }
        *heading = g_Task->direction;
    }
    AREA_TURN_SYNC();
}
