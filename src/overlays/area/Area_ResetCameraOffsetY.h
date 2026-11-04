/* Zeroes the camera Y offset and sets the camera refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F2F70 (area007), func_801F45C8 (area008), func_801F2D5C (area015), func_801F2D88 (area023), func_801F5DE8 (area077), func_801F3D34 (area080), func_801F2D64 (area081), func_801F3680 (area100), func_801F4208 (area119), func_801F53D0 (area134), func_801F4930 (area188) */
MATCH void Area_ResetCameraOffsetY(void) {
    g_AreaCameraOffsetY      = 0;
    g_AreaCameraRefreshCount = 2;
}
