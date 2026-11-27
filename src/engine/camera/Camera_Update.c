#include "engine/slus/slus.h"

/* steps the field camera toward its scroll goal, wraps the tile origin when it passes 0x200 either way (each wrap
 * calls one of the four edge refills), then rebuilds the rotation, view translation and projection matrix.
 */
/* func_801527E4 */
MATCH void Camera_Update(void) {
    SVECTOR view;
    VECTOR  trans;
    s32     dist;
    s32     value;
    s32     step_x;
    s32     step_y;
    s32     dir;
    s32     refilled;

    refilled = 0;
    if (g_GameAreaId == AREA_ID_DESERT_OF_DEATH_MAP) {
        func_801F2C04();
        return;
    }
    /* FAKE: the block around the x step and one local for the x position, then the y distance: together they give
     * both steps the retail register homes. */
    do {
        value = g_AreaCameraX;
        dist  = 0x800000 - ((value + 1) << 8) - (g_AreaScrollTargetX & ~0x7FFF);
        if (dist != 0) {
            g_AreaCameraMoving = 1;
            dir                = -1;
            if (dist > 0) {
                dir = 1;
            }
            step_x        = dir * g_AreaCameraSpeed;
            g_AreaCameraX = value + step_x;
            D_80149336 -= step_x;
            g_AreaTileRemainderY -= step_x;
        }
    } while (0);
    value = 0x800000 - (g_AreaCameraY << 8) - (g_AreaScrollTargetY & ~0x7FFF);
    if (value != 0) {
        g_AreaCameraMoving = 1;
        dir                = -1;
        if (value > 0) {
            dir = 1;
        }
        step_y = dir * g_AreaCameraSpeed;
        g_AreaCameraY += step_y;
        D_80149336 += step_y;
        g_AreaTileRemainderY -= step_y;
    }
    if (g_AreaCameraMoving != 0) {
        g_AreaCameraHeight += g_AreaCameraHeightDelta;
        if (g_AreaMapBundle.scroll == 0) {
            g_AreaTileRemainderY -= g_AreaCameraHeightDelta * 2;
        }
        g_AreaCameraRefreshCount = 2;
        dir                      = ((0x800000 - ((g_AreaCameraX + 1) << 8) - (g_AreaScrollTargetX & ~0x7FFF)) | (0x800000 - (g_AreaCameraY << 8) - (g_AreaScrollTargetY & ~0x7FFF)));
        if (dir == 0) {
            g_AreaCameraMoving = 0;
        }
    }
    if ((s16)D_80149336 >= 0x200) {
        Area_CellLoadColumnNext();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        D_80149336 -= 0x200;
    }
    if ((s16)D_80149336 < -0x1FF) {
        Area_CellLoadColumnPrev();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        D_80149336 += 0x200;
    }
    if ((s16)g_AreaTileRemainderY >= 0x200) {
        Area_CellLoadRowsNext();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        g_AreaTileRemainderY -= 0x200;
    }
    if ((s16)g_AreaTileRemainderY < -0x1FF) {
        Area_CellLoadRowsPrev();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        g_AreaTileRemainderY += 0x200;
    }
    if (refilled != 0) {
        Area_CellIndex();
    }
    if (g_AreaCameraAngle.vx != g_AreaPreviousCameraAngle.vx || g_AreaCameraAngle.vy != g_AreaPreviousCameraAngle.vy || g_AreaCameraAngle.vz != g_AreaPreviousCameraAngle.vz) {
        g_AreaCameraRefreshCount  = 3;
        g_AreaPreviousCameraAngle = g_AreaCameraAngle;
    }
    RotMatrix(&g_AreaCameraAngle, &g_CameraMatrix);
    setVector(&view, (u32)g_AreaCameraX >> 1, g_AreaCameraY >> 1, (u32)g_AreaCameraHeight >> 1);
    ApplyMatrix(&g_CameraMatrix, &view, &trans);
    D_801492FC = trans.vx + g_AreaCameraOffsetX;
    D_80149300 = trans.vy + g_AreaCameraOffsetY;
    D_80149304 = trans.vz + g_AreaCameraOffsetZ + 0x1194;
    SetRotMatrix(&g_CameraMatrix);
    SetTransMatrix(&g_CameraMatrix);
    if (g_AreaCameraRefreshCount != 0) {
        Area_CellDrawRing();
        g_AreaCameraRefreshCount -= 1;
    }
}
