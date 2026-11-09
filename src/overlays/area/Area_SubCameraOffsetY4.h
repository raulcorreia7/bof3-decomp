/* Subtract 4 from the camera Y offset and set the camera refresh count to 2.
 * One definition shared by the area overlays; every change here must verify
 * every member. */
/* func_801F3700 (area049), func_801F3658 (area100), func_801F2D6C (area133) */
MATCH void Area_SubCameraOffsetY4(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY - 4;
}
