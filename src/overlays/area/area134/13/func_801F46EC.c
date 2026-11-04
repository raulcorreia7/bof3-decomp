#include "area134_13.h"

MATCH void func_801F46EC(const void* sprite) {
    s16               screen[2];
    u16               size[2];
    const AreaSprite* work;
    const void*       object;
    POLY_FT4*         primitive;
    u8                shade;

    work      = (const AreaSprite*)sprite;
    object    = (const void*)((const u8*)sprite + 8u);
    primitive = (POLY_FT4*)g_GfxPrimCursor;

    SetPolyFT4(primitive);
    PSX_SET_SEMI_TRANSPARENT(primitive);

    Area_ProjectPoint(object, screen);
    size[0] = VOL(u16, work->half_size);
    size[1] = VOL(u16, work->half_size);
    func_801AFFD8(object, size, size);

    setXY4(primitive, screen[0] - ((s16)size[0] >> 1), screen[1] - ((s16)size[1] >> 1),
           (screen[0] - ((s16)size[0] >> 1)) + (s16)size[0], screen[1] - ((s16)size[1] >> 1),
           screen[0] - ((s16)size[0] >> 1), (screen[1] - ((s16)size[1] >> 1)) + (s16)size[1],
           (screen[0] - ((s16)size[0] >> 1)) + (s16)size[0], (screen[1] - ((s16)size[1] >> 1)) + (s16)size[1]);
    setUV4(primitive, 224u, 48u, 255u, 48u, 224u, 79u, 255u, 79u);
    primitive->clut  = GetClut(160, 483);
    primitive->tpage = GetTPage(0, 1, 704, 256);
    shade            = VOL(u8, work->flags_03);
    primitive->b0    = shade;
    primitive->g0    = shade;
    primitive->r0    = shade;

    GFX_AddPrim(1u, 0x28u);
}
