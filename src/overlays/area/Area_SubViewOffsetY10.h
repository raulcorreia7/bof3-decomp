/* Subtract 0xA from the area view Y offset and set the view refresh count to
 * 2. One definition shared by the area overlays; every change here must verify
 * every member. */
/* func_801F2F20 (area007), func_801F2D78 (area131) */
MATCH void Area_SubViewOffsetY10(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY - 0xA;
}
