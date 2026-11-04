/* Ends a turning step: begins the next one or stores the direction. Every change here must verify every member. */
/* func_801F58E8 (area104), func_801F5E2C (area121) */
MATCH void Area_FinishTurnStep(void) {
    u8* heading;

    heading = &D_80145E98;
    if (g_SpadWork->direction_08 != *heading) {
        if ((u8)Area_BeginTurnStep(g_SpadWork->direction_08, *heading) != 0) {
            return;
        }
        if ((u8)Area_BeginTurnStep(g_SpadWork->direction_08 ^ 4, *heading) != 0) {
            return;
        }
        *heading = g_SpadWork->direction_08;
    }
    AREA_TURN_SYNC();
}
