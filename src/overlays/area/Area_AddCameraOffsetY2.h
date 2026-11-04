/* Add 2 to the camera Y offset and set the camera refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F41B8 (area119), func_801F2E90 (area131), func_801F3170 (area136), func_801F48E0 (area188) */
MATCH void Area_AddCameraOffsetY2(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY + 2;
}
