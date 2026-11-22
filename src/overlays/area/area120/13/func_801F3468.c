#include "area120_13.h"

MATCH void func_801F3468(AreaRow* row) {
    SVECTOR screen[7];
    TILE_1* dot;
    TILE*   tile;
    u8      blue;

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Area_CellAddPrim(row->x, row->z, 0, 0xC);
    Camera_ProjectPoint(&row->x, (DVECTOR*)&screen[0]);

    dot = (TILE_1*)g_GfxPrimCursor;
    SetTile1(dot);
    SetSemiTrans(dot, 1);
    setXY0(dot, screen[0].vx, screen[0].vy);
    dot->g0 = 0x80;
    dot->r0 = 0x80;
    blue    = (rand() & 1) << 7;
    dot->b0 = blue;
    Area_CellAddPrim(row->x, row->z, 0, 0xC);

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, screen[0].vx - 1, screen[0].vy - 1);
    tile->w  = 3;
    tile->h  = 3;
    tile->g0 = 0x20;
    tile->r0 = 0x20;
    blue     = (rand() & 1) << 5;
    tile->b0 = blue;
    Area_CellAddPrim(row->x, row->z, 0, 0x10);
}
