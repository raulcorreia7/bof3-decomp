/* Loads the area camera Z offset with -0x100 and the refresh countdown
 * with 2.
 */
/* func_801F2D18, func_801F3E00 */
MATCH void Area_SetCameraZOffset(void) {
g_AreaCameraOffsetZ      = -0x100;
    g_AreaCameraRefreshCount = 2;
}
