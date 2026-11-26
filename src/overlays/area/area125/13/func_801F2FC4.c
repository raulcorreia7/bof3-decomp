#include "area125_13.h"

MATCH void func_801F2FC4(void* sprite) {
    DVECTOR               screen;
    u16                   size[2];
    s16                   buf[8];
    AreaQuadSprite*       work;
    s32*                  object;
    POLY_FT4*             primitive;

    work      = sprite;
    object    = &work->origin.x;
    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    PSX_SET_SEMI_TRANSPARENT(primitive);

    Camera_ProjectPoint(object, &screen);
    size[0] = work->half_size;
    size[1] = work->half_size;
    Game_ProjectWorldPoint(object, size, size);

    setXY4(primitive, screen.vx - ((s16)size[0] >> 1), screen.vy - ((s16)size[1] >> 1), (screen.vx - ((s16)size[0] >> 1)) + size[0], screen.vy - ((s16)size[1] >> 1), screen.vx - ((s16)size[0] >> 1),
           (screen.vy - ((s16)size[1] >> 1)) + size[1], (screen.vx - ((s16)size[0] >> 1)) + size[0], (screen.vy - ((s16)size[1] >> 1)) + size[1]);
    setUV4(primitive, 224u, 48u, 255u, 48u, 224u, 79u, 255u, 79u);
    setClut(primitive, 160, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    setRGB0(primitive, work->shade, (work->shade >> 2) * 3, work->shade >> 1);

    Area_CellAddPrim(work->origin.x, work->origin.y, 3, sizeof(POLY_FT4));
}
