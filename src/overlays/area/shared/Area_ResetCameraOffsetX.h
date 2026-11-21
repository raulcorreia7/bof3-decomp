/* Zeroes the camera X offset and sets the camera refresh count to 2. */
/* func_801F455C (area008), func_801F51E4 (area134) */
MATCH void Area_ResetCameraOffsetX(void) {
    g_AreaCameraOffsetX      = 0;
    g_AreaCameraRefreshCount = 2;
}
