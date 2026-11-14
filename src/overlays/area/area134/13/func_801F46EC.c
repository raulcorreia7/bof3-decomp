#include "area134_13.h"

MATCH void func_801F46EC(const void* sprite) {
    DVECTOR           screen;
    u16               size[2];
    const AreaSprite* work;
    s32*              object;
    POLY_FT4*         primitive;
    u8                shade;

    work      = (const AreaSprite*)sprite;
    object    = (const void*)((const u8*)sprite + 8u);
    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);

    Area_ProjectPoint(object, &screen);
    size[0] = VOL(u16, work->half_size);
    size[1] = VOL(u16, work->half_size);
    Game_ProjectWorldPoint(object, size, size);

    setXY4(primitive, screen.vx - ((s16)size[0] >> 1), screen.vy - ((s16)size[1] >> 1), (screen.vx - ((s16)size[0] >> 1)) + size[0], screen.vy - ((s16)size[1] >> 1), screen.vx - ((s16)size[0] >> 1),
           (screen.vy - ((s16)size[1] >> 1)) + size[1], (screen.vx - ((s16)size[0] >> 1)) + size[0], (screen.vy - ((s16)size[1] >> 1)) + size[1]);
    setUV4(primitive, 224u, 48u, 255u, 48u, 224u, 79u, 255u, 79u);
    setClut(primitive, 160, STAGE_PALETTE_Y + 3);
    primitive->tpage = GetTPage(0, 1, 704, 256);
    shade            = VOL(u8, work->flags_03);
    primitive->b0    = shade;
    primitive->g0    = shade;
    primitive->r0    = shade;

    GFX_AddPrim(1u, sizeof(POLY_FT4));
}
