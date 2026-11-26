#include "area189_13.h"

#ifdef NON_MATCHING
/* Draws the rain sheet: three placed tiles and a three-tile column stepping down the screen. */
NON_MATCHING void func_801F43E8(s32 scale) {
    TILE_1* tile;
    s16     cell_x;
    s16     cell_y;
    s32     shade;
    s32     x;
    s16     y;
    s32     row_y;
    s32     cy;
    s32     dx;
    s32     dy;
    u32     angle;
    s32     step;
    s32     i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    func_801F497C(sizeof(TILE_1));
    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 1);
    shade    = (scale << 8) - scale;
    tile->y0 = 0x2D;
    angle    = g_AreaCameraAngle.vz + 0x200;
    tile->x0 = ((angle & 0xFFF) * 5) >> 4;
    shade    = shade / 128;
    tile->r0 = shade;
    tile->g0 = (rand() & 0x7F) * scale / 128;
    tile->b0 = (rand() & 0x7F) * scale / 128;
    func_801F497C(sizeof(TILE_1));
    func_801F4B64(tile);

    cell_y   = g_AreaTargetCellY;
    tile     = (TILE_1*)g_GfxPrimCursor;
    y        = cell_y / 85 - 1;
    tile->y0 = y;
    if ((u16)y < 0x5A) {
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        angle    = g_AreaCameraAngle.vz + 0x400;
        tile->x0 = ((angle & 0xFFF) * 5) >> 4;
        tile->r0 = shade;
        tile->g0 = (rand() & 0x7F) * scale / 128;
        tile->b0 = (rand() & 0x7F) * scale / 128;
        func_801F497C(sizeof(TILE_1));
        func_801F4B64(tile);
    }

    dy = 0x1400 - g_AreaTargetCellY;
    if (dy < 0) {
        dy = -dy;
    }
    y      = dy * dy / 98304;
    tile   = (TILE_1*)g_GfxPrimCursor;
    cell_x = g_AreaTargetCellX;
    if ((cell_x >> 8) >= 0xF) {
        y = (cell_x - 0xF00) / 25 + (y + 8);
    } else {
        y = y + 8;
    }
    tile->y0 = y;
    if ((u16)y < 0x5A) {
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        tile->x0 = (((g_AreaCameraAngle.vz - 0x200) * 5) >> 4) + (g_AreaTargetCellY - 0x1480) / 17;
        tile->r0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        tile->g0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        tile->b0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        func_801F497C(sizeof(TILE_1));
        func_801F4B64(tile);
    }

    dx    = abs(g_AreaTargetCellX - 0x1480);
    dy    = abs(g_AreaTargetCellY - 0x1380);
    dx    = dx > 0x900 ? 0x900 : dx;
    dy    = dy > 0x400 ? 0x400 : dy;
    row_y = (0xD00 - (dx + dy)) / 43 + 0x14;
    row_y = row_y < 0x28 ? 0x28 : row_y;
    x     = g_AreaTargetCellX;
    if (x < 0xB00) {
        x = 0xB00;
    }
    x  = x > 0x1E00 ? 0x1E00 : x;
    cy = g_AreaTargetCellY;
    if (cy < 0xF00) {
        cy = 0xF00;
    }
    cy = cy > 0x1800 ? 0x1800 : cy;
    for (i = 0, step = 0; i < 3; i++) {
        tile     = (TILE_1*)g_GfxPrimCursor;
        tile->y0 = row_y;
        if ((s16)row_y < 0x5A) {
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            angle    = ratan2(cy - 0x1380, x - 0x1480) + g_AreaCameraAngle.vz + 0x633;
            tile->x0 = ((angle & 0xFFF) * 5 >> 4) - step;
            tile->r0 = (rand() & 0x7F) * scale / 128;
            tile->g0 = (rand() & 0x7F) * scale / 128;
            tile->b0 = ((scale << 8) - scale) / 128;
            func_801F497C(sizeof(TILE_1));
        }
        step += 0xA;
        row_y += 8;
    }
}
#else
INCLUDE_ASM(func_801F43E8);
#endif
