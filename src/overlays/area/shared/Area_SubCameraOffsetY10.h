/* Subtract 0xA from the camera Y offset and set the camera refresh count to 2. */
/* func_801F2F20 (area007), func_801F2D78 (area131) */
MATCH void Area_SubCameraOffsetY10(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY - 0xA;
}
