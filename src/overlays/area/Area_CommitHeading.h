/* Stores the actor's direction_08 into the last-heading byte D_80145E98 when
 * it differs, unless the image's AREA_HEADING_BLOCKED refuses a turn to it or
 * to its opposite (direction ^ 4), then runs AREA_HEADING_STEP. One
 * definition shared by the world area overlays; every change here must verify
 * every member. */
/* func_801F58E8 (area104), func_801F5E2C (area121) */
MATCH void Area_CommitHeading(void) {
    u8* heading;

    heading = &D_80145E98;
    if (g_SpadWork->direction_08 != *heading) {
        if ((u8)AREA_HEADING_BLOCKED(g_SpadWork->direction_08, *heading) != 0) {
            return;
        }
        if ((u8)AREA_HEADING_BLOCKED(g_SpadWork->direction_08 ^ 4, *heading) != 0) {
            return;
        }
        *heading = g_SpadWork->direction_08;
    }
    AREA_HEADING_STEP();
}
