#include "area052_13.h"

MATCH void func_801F2EC8(AreaEffectRow* row) {
    DVECTOR   screen;
    u16       size[2];
    VECTOR    object;
    POLY_FT4* primitive;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256));
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);

    screen.vx = row->unk_10 >> 6;
    /* The row's four leading words are the projection input; retail copies them whole, and no
     * view type describes that prefix. */
    memcpy(&object, row, sizeof(object));
    object.vz <<= 8;

    Game_ProjectWorldPoint(&object, &screen, size);
    Area_ProjectPoint(&object.vx, &screen);

    primitive->x0 = primitive->x2 = screen.vx - size[0];
    primitive->x1 = primitive->x3 = screen.vx + size[0];
    primitive->y0 = primitive->y1 = screen.vy - size[0];
    primitive->y2 = primitive->y3 = screen.vy + size[0];
    setClut(primitive, 160, STAGE_PALETTE_Y + 3);
    setTPage(primitive, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    setUV4(primitive, 224, 48, 255, 48, 224, 79, 255, 79);
    setRGB0(primitive, row->unk_14, row->unk_14, row->unk_14);
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
