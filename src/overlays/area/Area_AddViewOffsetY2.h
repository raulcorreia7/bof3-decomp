/* Add 2 to the area view Y offset and set the view refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F41B8 (area119), func_801F2E90 (area131), func_801F48E0 (area188) */
MATCH void Area_AddViewOffsetY2(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY + 2;
}
