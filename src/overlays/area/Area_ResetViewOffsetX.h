/* Zeroes the area view X offset and sets the view refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F455C (area008), func_801F51E4 (area134) */
MATCH void Area_ResetViewOffsetX(void) {
    g_AreaViewOffsetX      = 0;
    g_AreaViewRefreshCount = 2;
}
