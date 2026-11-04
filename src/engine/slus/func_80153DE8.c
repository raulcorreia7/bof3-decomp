#include "engine/slus/slus.h"

/* initializes the field map renderer: sets the geometry screen, offset and back color, resets the 0x400 double
 * FT4 primitives, seeds the camera position and scroll state from g_AreaScrollTargetX/g_AreaScrollTargetY, clears the
 * 0x38 by 0x1C cell table, fills the identity draw order and builds the first view through func_80154438, func_80157F98
 * and func_80158B24.
 */
/* nonmatching 70.04%: opcode@+0x004c; the byte-offset reset loop reaches it, but retail keeps the row and prim
 * counters in different saved registers. Pinning them (work/.../best.c, 75.61%) still leaves the +0x00e4 vector
 * destination in a2 instead of a3. resume: a source shape that changes the vector/state copy lifetimes. */
#ifdef NON_MATCHING
NON_MATCHING void func_80153DE8(void) {
    POLY_FT4* poly;
    u16*      order;
    u8*       prim;
    u8*       prim_base;
    s32       row_offset;
    s32       row;
    s32       col;
    s32       i;
    s32       primitive_offset;
    s32       primitive_row_offset;
    u16       height;

    SetGeomScreen(1000);
    SetGeomOffset(160, 120);
    SetBackColor(120, 120, 120);
    prim_base = (u8*)g_AreaCellPrims;
    for (row_offset = 0, row = 0; row_offset < 1024; row_offset++, row += 0x50) {
        for (i = 0, primitive_row_offset = row, primitive_offset = row, prim = prim_base; i < 2;
             primitive_offset += 0x28, i++, prim += 0x28) {
            poly = (POLY_FT4*)(prim + primitive_row_offset);
            SetPolyFT4(poly);
            SetShadeTex(poly, 0);
            *(u16*)(((u8*)g_AreaCellPrims + 0x1E) + primitive_offset) = 0;
            *(u16*)(((u8*)g_AreaCellPrims + 0x26) + primitive_offset) = 0;
        }
    }
    *(s16*)(&g_AreaCameraAngle.vx) = -682;
    g_AreaCameraAngle.vy           = 0;
    g_AreaCameraAngle.vz           = ANGLE_45;
    *(SVECTOR*)&D_801492E0         = *&g_AreaCameraAngle;
    g_AreaCellPrims[0][0].x0       = 0;
    g_AreaCellPrims[0][0].y0       = 0;
    g_AreaCellPrims[0][0].x1       = 0;
    g_AreaCellPrims[0][0].y1       = 0;
    g_AreaCellPrims[0][0].x2       = 0;
    g_AreaCellPrims[0][0].y2       = 0;
    g_AreaCellPrims[0][0].x3       = 0;
    g_AreaCellPrims[0][0].y3       = 0;
    g_AreaCellPrims[0][1].x0       = 0;
    g_AreaCellPrims[0][1].y0       = 0;
    g_AreaCellPrims[0][1].x1       = 0;
    g_AreaCellPrims[0][1].y1       = 0;
    g_AreaCellPrims[0][1].x2       = 0;
    g_AreaCellPrims[0][1].y2       = 0;
    g_AreaCellPrims[0][1].x3       = 0;
    g_AreaCellPrims[0][1].y3       = 0;
    g_AreaCameraOffsetZ            = 0;
    g_AreaCameraOffsetY            = 0;
    g_AreaCameraOffsetX            = 0;
    D_80149310                     = 0x7FFF - ((s32)g_AreaScrollTargetX >> 8);
    D_80149314                     = 0x8000 - ((s32)g_AreaScrollTargetY >> 8);
    g_AreaTileOriginX              = ((s32)g_AreaScrollTargetX >> 0x10) - 0x18;
    g_AreaTileOriginY              = ((s32)g_AreaScrollTargetY >> 0x10) + 3;
    if (g_GameRequestFlags & 8) {
        g_AreaCameraHeight = 0;
    } else {
        g_AreaCameraHeight = (s32)Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
    }
    if (g_GameRequestFlags & 1) {
        D_8014933A = 0x80;
    } else {
        D_8014933A = 0;
    }
    height     = g_AreaMapBundle.scroll_1E;
    D_8014933D = 0;
    if (height == 0) {
        height = g_AreaCameraHeight * -2;
    }
    g_AreaTileRemainderY     = height;
    D_80149336               = 0;
    g_AreaCameraStep         = 0;
    g_AreaCameraHeightStep   = 0;
    D_80149340               = 0;
    g_AreaSceneMode          = 0;
    g_AreaCameraRefreshCount = 3;
    g_AreaCellCodes          = (g_AreaMapBundle.byte_code_off4_14 * 4) + (MAP_BUNDLE_BASE + 0x00);
    for (row = 0; row < 56; row++) {
        for (col = 0; col < 28; col++) {
            g_AreaCells[row][col].prim_id = 0;
            Area_ProbeCell(row, col, &g_AreaCells[row][col]);
        }
    }
    order = &g_AreaCellPrimFreeIds[0x3FF];
    for (i = 0x3FF; i >= 0; i--) {
        *order = i;
        order--;
    }
    g_AreaCellPrimFreeIndex = 1;
    g_AreaGridColCursor     = 0x1B;
    g_AreaGridRowCursor     = 0x37;
    func_80154438();
    Area_RunBundleOpcodes();
    Area_IndexCells();
}
#else
INCLUDE_ASM(func_80153DE8);
#endif
