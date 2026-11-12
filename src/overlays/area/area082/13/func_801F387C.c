#include "area082_13.h"

MATCH void func_801F387C(AreaSpark* spark) {
    DVECTOR screen;
    s32     unused[4]; /* FAKE: pads the frame to retail size. */
    TILE_1* tile;
    u8      shade;

    Area_ProjectPoint(&spark->pos.x, &screen);
    tile = (TILE_1*)g_GfxPrimCursor;
    SetTile1(tile);
    SetSemiTrans(tile, 0);
    tile->x0 = screen.vx;
    tile->y0 = screen.vy;
    shade    = -(rand() & 0x1);
    tile->b0 = shade;
    tile->g0 = shade;
    tile->r0 = shade;
    Area_AddCellPrim(spark->pos.x, spark->pos.y, 0, 12);
}
