#include "area030_04.h"

/* Configures the shared 8x8 sprite primitive as the dim AREA030 icon
 * marker and appends it with the caller's semi-transparency mode. */
MATCH void func_801D18CC(s16 sprite_x, s16 sprite_y, u8 icon_index) {
    SPRT_8* primitive;

    primitive = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(primitive);
    setRGB0(primitive, 128, 128, 128);
    primitive->clut = 0x7A40;
    primitive->u0   = 184;
    setXY0(primitive, sprite_x, sprite_y);
    primitive->v0 = 72;
    GFX_AddPrim(icon_index, 0x10);
}
