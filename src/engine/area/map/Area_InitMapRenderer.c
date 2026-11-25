#define FAKE_DECL_AREA_SCROLL_TARGET_VOLATILE
#define FAKE_DECL_AREA_SCROLL_TARGET_Y_VOLATILE
#include "engine/slus/slus.h"

/* initializes the field map renderer: sets the geometry screen, offset and back color, resets the 0x400 double
 * FT4 primitives, seeds the camera position and scroll state from g_AreaScrollTargetX/g_AreaScrollTargetY, clears the
 * 0x38 by 0x1C cell table, fills the identity draw order and builds the first view through Area_BundleApplyObjects, func_80157F98
 * and func_80158B24.
 */
/* func_80153DE8 */
#ifdef NON_MATCHING
NON_MATCHING void Area_InitMapRenderer(void) {
    s32       row;
    s32       col;
    s32       i;
    AreaCell* cell;
    s32       target_x;
    s32       target_y;

    SetGeomScreen(1000);
    SetGeomOffset(160, 120);
    SetBackColor(120, 120, 120);
    for (row = 0; row < 1024; row++) {
        for (i = 0; i < 2; i++) {
            SetPolyFT4(&g_AreaCellPrims[row][i]);
            SetShadeTex(&g_AreaCellPrims[row][i], 0);
            g_AreaCellPrims[row][i].pad1 = 0;
            g_AreaCellPrims[row][i].pad2 = 0;
        }
    }
    g_AreaCameraAngle.vx      = -682;
    g_AreaCameraAngle.vy      = 0;
    g_AreaCameraAngle.vz      = ANGLE_45;
    g_AreaPreviousCameraAngle = g_AreaCameraAngle;
    setXY4(&g_AreaCellPrims[0][0], 0, 0, 0, 0, 0, 0, 0, 0);
    setXY4(&g_AreaCellPrims[0][1], 0, 0, 0, 0, 0, 0, 0, 0);
    g_AreaCameraOffsetZ = 0;
    g_AreaCameraOffsetY = 0;
    g_AreaCameraOffsetX = 0;
    target_x            = g_AreaScrollTargetX;
    target_y            = g_AreaScrollTargetY;
    g_AreaCameraX       = 0x7FFF - (target_x >> 8);
    g_AreaCameraY       = 0x8000 - (target_y >> 8);
    g_AreaTileOriginX   = (target_x >> 0x10) - 24;
    g_AreaTileOriginY   = (target_y >> 0x10) + 3;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_FISHING) {
        g_AreaCameraHeight = 0;
    } else {
        g_AreaCameraHeight = (s32)Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY);
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) {
        D_8014933A = 0x80;
    } else {
        D_8014933A = 0;
    }
    g_AreaCellPacketCount = 0;
    if (g_AreaMapBundle.scroll != 0) {
        g_AreaTileRemainderY = g_AreaMapBundle.scroll;
    } else {
        g_AreaTileRemainderY = -g_AreaCameraHeight * 2;
    }
    D_80149336                = 0;
    g_AreaCameraSpeed         = 0;
    g_AreaCameraHeightDelta   = 0;
    g_AreaHeightOffsetEnabled = 0;
    g_AreaSceneMode           = 0;
    g_AreaCameraRefreshCount  = 3;
    g_AreaCellCodes           = (g_AreaMapBundle.byte_code_offset * 4) + (MAP_BUNDLE_BASE + 0x00);
    for (row = 0; row < AREA_CELL_GRID_ROWS; row++) {
        for (col = 0; col < AREA_CELL_GRID_COLS; col++) {
            cell            = &g_AreaCells[row][col];
            cell->prim_slot = 0;
            Area_CellGet(row, col, cell);
        }
    }
    for (i = 0x3FF; i >= 0; i--) {
        g_AreaCellPrimFreeSlots[i] = i;
    }
    g_AreaCellPrimFreeIndex = 1;
    g_AreaGridColCursor     = 0x1B;
    g_AreaGridRowCursor     = 0x37;
    Area_BundleApplyObjects();
    Area_BundleRunOpcodes();
    Area_CellIndex();
}
#else
INCLUDE_ASM(Area_InitMapRenderer);
#endif
