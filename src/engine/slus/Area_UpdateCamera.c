#include "engine/slus/slus.h"

/* steps the field camera toward its scroll goal, wraps the tile origin when it passes 0x200 either way (each wrap calls one of the four edge refills). */
/* func_801527E4 */
MATCH void Area_UpdateCamera(void) {
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
    /* FAKE: the order lock around the x step and one local for the x position, then the y distance: together they give
     * both steps the retail register homes. */
    FAKE_ORDER_LOCK_BEGIN
        value = g_AreaCameraX;
        dist  = 0x800000 - ((value + 1) << 8) - (g_AreaScrollTargetX & ~0x7FFF);
        if (dist != 0) {
            g_AreaCameraMoving = 1;
            dir                = -1;
            if (dist > 0) {
                dir = 1;
            }
            step_x        = dir * g_AreaCameraStep;
            g_AreaCameraX = value + step_x;
            D_80149336 -= step_x;
            g_AreaTileRemainderY -= step_x;
        }
    FAKE_ORDER_LOCK_END;
    value = 0x800000 - (g_AreaCameraY << 8) - (g_AreaScrollTargetY & ~0x7FFF);
    if (value != 0) {
        g_AreaCameraMoving = 1;
        dir                = -1;
        if (value > 0) {
            dir = 1;
        }
        step_y = dir * g_AreaCameraStep;
        g_AreaCameraY += step_y;
        D_80149336 += step_y;
        g_AreaTileRemainderY -= step_y;
    }
    if (g_AreaCameraMoving != 0) {
        g_AreaCameraHeight += g_AreaCameraHeightStep;
        if (g_AreaMapBundle.scroll_1E == 0) {
            g_AreaTileRemainderY -= g_AreaCameraHeightStep * 2;
        }
        g_AreaCameraRefreshCount = 2;
        dir                      = ((0x800000 - ((g_AreaCameraX + 1) << 8) - (g_AreaScrollTargetX & ~0x7FFF)) |
                                    (0x800000 - (g_AreaCameraY << 8) - (g_AreaScrollTargetY & ~0x7FFF)));
        if (dir == 0) {
            g_AreaCameraMoving = 0;
        }
    }
    if ((s16)D_80149336 >= 0x200) {
        Area_LoadCellColumnNext();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        D_80149336 -= 0x200;
    }
    if ((s16)D_80149336 < -0x1FF) {
        Area_LoadCellColumnPrev();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        D_80149336 += 0x200;
    }
    if ((s16)g_AreaTileRemainderY >= 0x200) {
        Area_LoadCellRowsNext();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        g_AreaTileRemainderY -= 0x200;
    }
    if ((s16)g_AreaTileRemainderY < -0x1FF) {
        Area_LoadCellRowsPrev();
        refilled                 = 1;
        g_AreaCameraRefreshCount = 2;
        g_AreaTileRemainderY += 0x200;
    }
    if (refilled != 0) {
        Area_IndexCells();
    }
    if (g_AreaCameraAngle.vx != *(s16*)&D_801492E0 || g_AreaCameraAngle.vy != D_801492E2 ||
        g_AreaCameraAngle.vz != D_801492E4) {
        g_AreaCameraRefreshCount = 3;
        *(SVECTOR*)&D_801492E0   = *&g_AreaCameraAngle;
    }
    RotMatrix(&g_AreaCameraAngle, &g_CameraMatrix);
    view.vx = (u32)g_AreaCameraX >> 1;
    view.vy = g_AreaCameraY >> 1;
    view.vz = (u32)g_AreaCameraHeight >> 1;
    ApplyMatrix(&g_CameraMatrix, &view, &trans);
    D_801492FC = trans.vx + g_AreaCameraOffsetX;
    D_80149300 = trans.vy + g_AreaCameraOffsetY;
    D_80149304 = trans.vz + g_AreaCameraOffsetZ + 0x1194;
    SetRotMatrix(&g_CameraMatrix);
    SetTransMatrix(&g_CameraMatrix);
    if (g_AreaCameraRefreshCount != 0) {
        func_801530D0();
        g_AreaCameraRefreshCount -= 1;
    }
}
