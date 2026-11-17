#include "area189_13.h"

MATCH void func_801F2C04(void) {
    SVECTOR view;
    VECTOR  trans;

    g_AreaCameraX = (0x800000 - g_AreaScrollTargetX) >> 8;
    g_AreaCameraY = (0x800000 - g_AreaScrollTargetY) >> 8;
    if (g_AreaCameraAngle.vx != g_AreaPreviousCameraAngle.vx || g_AreaCameraAngle.vy != g_AreaPreviousCameraAngle.vy || g_AreaCameraAngle.vz != g_AreaPreviousCameraAngle.vz) {
        g_AreaCameraRefreshCount  = 3;
        g_AreaPreviousCameraAngle = g_AreaCameraAngle;
    }
    RotMatrix(&g_AreaCameraAngle, &g_CameraMatrix);
    /* The view wraps around the cell grid origin into the 15-bit vertex range. */
    view.vx = (((u32)g_AreaCameraX >> 1) + AREA_CELL_ORIGIN) & 0x7FFF;
    view.vx -= AREA_CELL_ORIGIN;
    view.vy = (((u32)g_AreaCameraY >> 1) + AREA_CELL_ORIGIN) & 0x7FFF;
    view.vy -= AREA_CELL_ORIGIN;
    view.vz = (u32)g_AreaCameraHeight >> 1;
    ApplyMatrix(&g_CameraMatrix, &view, &trans);
    g_CameraMatrix.t[0] = trans.vx + g_AreaCameraOffsetX;
    g_CameraMatrix.t[1] = trans.vy + g_AreaCameraOffsetY;
    g_CameraMatrix.t[2] = trans.vz + g_AreaCameraOffsetZ + 0x1194;
    SetRotMatrix(&g_CameraMatrix);
    SetTransMatrix(&g_CameraMatrix);
    if (g_AreaCameraRefreshCount != 0) {
        func_801F2DE0();
        g_AreaCameraRefreshCount -= 1;
    }
}
