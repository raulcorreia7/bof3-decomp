/* Zero the camera Z offset and set the camera refresh count to 2. */
/* func_801F2D38 (area039), func_801F3E20 (area041), func_801F2C24 (area099) */
MATCH void Area_ResetCameraOffsetZ(void) {
    g_AreaCameraOffsetZ      = 0;
    g_AreaCameraRefreshCount = 2;
}
