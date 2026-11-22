#include "area067_14.h"

/* Draws the eight rays of a ripple from its centre. */
MATCH void func_801F31C8(AreaRippleQuad* quad) {
    LINE_G2* prim;
    u8       i;
    u16      angle;

    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Area_CellAddPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
    i = 0;
    do {
        angle = quad->height + (i << 9);
        prim  = (LINE_G2*)g_GfxPrimCursor;
        SetLineG2(prim);
        SetSemiTrans(prim, 1);
        prim->x0      = quad->x;
        prim->y0      = quad->y;
        prim->x1      = quad->x + ((quad->radius * rcos(angle)) >> ((i & 1) + 12));
        LOH(prim->y1) = quad->y + ((quad->radius * rsin(angle)) >> ((i & 1) + 12));
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 0, 0, 0);
        Area_CellAddPrim(D_801F53A0, D_801F53A4, 4, sizeof(LINE_G2));
        i++;
    } while (i < 8);
    func_801F3394(quad);
    GFX_SET_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Area_CellAddPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
}
