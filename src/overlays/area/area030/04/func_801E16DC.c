#include "area030_04.h"

/* Configures the dim semi-transparent AREA030 tile and appends it
 * after selecting graphics mode 4. */
MATCH void func_801E16DC(void) {
    TILE* primitive;

    func_801E0C80(4, 2);
    primitive = (TILE*)g_GfxPrimCursor;
    SetTile(primitive);
    primitive->b0 = 0x20;
    primitive->g0 = 0x20;
    primitive->r0 = 0x20;
    primitive->w  = 320;
    setXY0(primitive, 0, 0);
    primitive->h = 240;
    PSX_SET_SEMI_TRANSPARENT(primitive);
    GFX_AddPrim(2, 0x10);
}
