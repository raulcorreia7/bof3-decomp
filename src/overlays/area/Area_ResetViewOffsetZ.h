/* Zero the area view Z offset and set the view refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F2D38 (area039), func_801F3E20 (area041), func_801F2C24 (area099) */
MATCH void Area_ResetViewOffsetZ(void) {
    g_AreaViewOffsetZ      = 0;
    g_AreaViewRefreshCount = 2;
}
