/* Add 0xA to the camera Y offset and set the camera refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F2F48 (area007), func_801F2DA0 (area131) */
MATCH void Area_AddCameraOffsetY10(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY + 0xA;
}
