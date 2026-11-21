/* The statements of Area_ResetCameraOffsetY: zeroes the camera Y offset and sets the refresh count to 2. */
#define AREA_RESET_CAMERA_OFFSET_Y()  \
    do {                              \
        g_AreaCameraOffsetY      = 0; \
        g_AreaCameraRefreshCount = 2; \
    } while (0)
