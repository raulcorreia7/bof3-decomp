/* Subtract 2 from the camera Y offset and set the camera refresh count to 2.
 * One definition shared by the area overlays; every change here must verify
 * every member. */
/* func_801F41E0 (area119), func_801F2E68 (area131), func_801F4908 (area188) */
MATCH void Area_SubCameraOffsetY2(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY - 2;
}
