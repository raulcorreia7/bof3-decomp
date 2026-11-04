/* Subtract 4 from the area view Y offset and set the view refresh count to 2.
 * One definition shared by the area overlays; every change here must verify
 * every member. */
/* func_801F3700 (area049), func_801F3658 (area100), func_801F2D6C (area133) */
MATCH void Area_SubViewOffsetY4(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY - 4;
}
