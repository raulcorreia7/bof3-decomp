/* Add 4 to the area view Y offset and set the view refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F3728 (area049), func_801F3630 (area100), func_801F2D94 (area133) */
MATCH void Area_AddViewOffsetY4(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY + 4;
}
