#include "area189_13.h"

#ifdef NON_MATCHING
/* Draws the rain sheet: three background tiles whose screen positions follow the target cell and the
 * camera turn, then a three-tile column stepping down the screen, all shaded by `scale`. */
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
    tile->x0 = (((g_AreaCameraAngle.vy + 0x200) & 0xFFF) * 5) >> 4;
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
        tile->x0 = (((g_AreaCameraAngle.vy + 0x400) & 0xFFF) * 5) >> 4;
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
        tile->x0 = ((g_AreaCameraAngle.vy - 0x200) * 5) >> 4;
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
    if (dx > 0x900) {
        dx = 0x900;
    }
    if (dy > 0x400) {
        dy = 0x400;
    }
    y = (0xD00 - dx - dy) / 43 + 0x14;
    if (y > 0x28) {
        y = 0x28;
    }
    x = cell_x;
    if (x < 0xB00) {
        x = 0xB00;
    }
    if (x > 0x1E00) {
        x = 0x1E00;
    }
    cell_y = g_AreaTargetCellY;
    if (cell_y < 0xF00) {
        cell_y = 0xF00;
    }
    if (cell_y > 0x1800) {
        cell_y = 0x1800;
    }
    for (i = 0, step = 0; i < 3; i++) {
        tile     = (TILE_1*)g_GfxPrimCursor;
        tile->y0 = y;
        if ((s16)y < 0x5A) {
            SetTile1(tile);
            SetSemiTrans(tile, 1);
            angle    = ratan2(cell_y - 0x1380, x - 0x1480) + g_AreaCameraAngle.vy + 0x633;
            tile->x0 = ((angle & 0xFFF) * 5 >> 4) - step;
            tile->r0 = (rand() & 0x7F) * scale / 128;
            tile->g0 = (rand() & 0x7F) * scale / 128;
            tile->b0 = shade;
            func_801F497C(sizeof(TILE_1));
        }
        step += 0xA;
        y += 8;
    }
}
#else
INCLUDE_ASM(func_801F43E8);
#endif
