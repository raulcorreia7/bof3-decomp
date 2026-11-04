/* Subtract 0x14 from the area view Y offset and set the view refresh count to
 * 2. One definition shared by the area overlays; every change here must verify
 * every member. */
/* func_801F2D0C (area015), func_801F3410 (area049), func_801F3CE4 (area080), func_801F2DC8 (area131) */
MATCH void Area_SubViewOffsetY20(void) {
    g_AreaViewRefreshCount = 2;
    g_AreaViewOffsetY      = (u16)g_AreaViewOffsetY - 0x14;
}
