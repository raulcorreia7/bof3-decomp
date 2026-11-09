/* Add 4 to the camera Y offset and set the camera refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F3728 (area049), func_801F3630 (area100), func_801F2D94 (area133) */
MATCH void Area_AddCameraOffsetY4(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY + 4;
}
