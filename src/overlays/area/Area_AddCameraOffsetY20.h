/* Add 0x14 to the camera Y offset and set the camera refresh count to 2. One
 * definition shared by the area overlays; every change here must verify every
 * member. */
/* func_801F2D34 (area015), func_801F33E8 (area049), func_801F5DC0 (area077), func_801F3D0C (area080), func_801F2DF0 (area131), func_801F4578 (area008), func_801F3258 (area026) */
MATCH void Area_AddCameraOffsetY20(void) {
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY      = (u16)g_AreaCameraOffsetY + 0x14;
}
