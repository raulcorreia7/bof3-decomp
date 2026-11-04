/* Add 0xA to the area view Y offset and set the view refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F2F48 (area007), func_801F2DA0 (area131) */
MATCH void Area_AddViewOffsetY10(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY + 0xA;
}
