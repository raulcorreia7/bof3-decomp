#include "area189_13.h"

#ifdef NON_MATCHING
/* Draws the rain sheet: three placed tiles and a three-tile column stepping down the screen. */
NON_MATCHING void func_801F43E8(s32 scale) {
    TILE_1* tile;
    s16     cell_x;
    s16     cell_y;
    s32     shade;
    s32     x;
    s32     y;
    s32     dx;
    s32     dy;
    s32     angle;
    s32     step;
    s32     i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), 0);
    func_801F497C(sizeof(TILE_1));
    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 1);
    shade    = ((scale << 8) - scale) / 128;
    tile->y0 = 0x2D;
    tile->x0 = (((g_AreaCameraAngle.vz + 0x200) & 0xFFF) * 5) >> 4;
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
        tile->x0 = (((g_AreaCameraAngle.vz + 0x400) & 0xFFF) * 5) >> 4;
        tile->r0 = shade;
        tile->g0 = (rand() & 0x7F) * scale / 128;
        tile->b0 = (rand() & 0x7F) * scale / 128;
        func_801F497C(sizeof(TILE_1));
        func_801F4B64(tile);
    }

    cell_x = g_AreaTargetCellX;
    cell_y = g_AreaTargetCellY;
    dy     = cell_y - 0x1400;
    if (dy < 0) {
        dy = -dy;
    }
    y = dy * dy / 98304 + 8;
    if ((s8)(cell_x >> 8) >= 0xF) {
        y += (cell_x - 0xF00) / 25;
    }
    tile     = (TILE_1*)g_GfxPrimCursor;
    tile->y0 = y;
    if ((u16)y < 0x5A) {
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        tile->x0 = (((g_AreaCameraAngle.vz - 0x200) * 5) >> 4) + (cell_y - 0x1480) / 17;
        tile->r0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        tile->g0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        tile->b0 = ((rand() + 0x80) & 0xFF) * scale / 128;
        func_801F497C(sizeof(TILE_1));
        func_801F4B64(tile);
    }

    dx = cell_x - 0x1480;
    if (dx < 0) {
        dx = -dx;
    }
    dy = cell_y - 0x1380;
    if (dy < 0) {
        dy = -dy;
    }
    dx     = dx > 0x900 ? 0x900 : dx;
    dy     = dy > 0x400 ? 0x400 : dy;
    y      = (0xD00 - dx - dy) / 43 + 0x14;
    y      = y < 0x28 ? 0x28 : y;
    x      = cell_x;
    x      = x < 0xB00 ? 0xB00 : x;
    x      = x > 0x1E00 ? 0x1E00 : x;
    cell_y = g_AreaTargetCellY;
    cell_y = cell_y < 0xF00 ? 0xF00 : cell_y;
    cell_y = cell_y > 0x1800 ? 0x1800 : cell_y;
    for (i = 0, step = 0; i < 3; i++) {
        tile     = (TILE_1*)g_GfxPrimCursor;
        tile->y0 = y;
        if ((s16)y < 0x5A) {
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            angle    = ratan2(cell_y - 0x1380, x - 0x1480) + g_AreaCameraAngle.vz + 0x633;
            tile->x0 = ((angle & 0xFFF) * 5 >> 4) - step;
            tile->r0 = (rand() & 0x7F) * scale / 128;
            tile->g0 = (rand() & 0x7F) * scale / 128;
            tile->b0 = ((scale << 8) - scale) / 128;
            func_801F497C(sizeof(TILE_1));
        }
        step += 0xA;
        y += 8;
    }
}
#else
INCLUDE_ASM(func_801F43E8);
#endif
