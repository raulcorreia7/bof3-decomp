#include "area067_14.h"

MATCH void func_801F3AD8(AreaRippleQuad* quad) {
    POLY_G4* prim;
    u8       color;
    s16      shade;
    u16      angle;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), NULL);
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
    shade = quad->angle;
    angle = 0;
    for (i = 0; i < 8; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = prim->x1 = quad->x + ((quad->radius * rcos(angle)) >> 12);
        prim->y0            = 0;
        prim->y1            = quad->y + ((quad->radius * rsin(angle)) >> 13);
        color               = shade;
        if (shade >= 0x100) {
            color = 0xFF;
        }
        if (shade < 0) {
            color = 0;
        }
        setRGB0(prim, color, color, color);
        setRGB1(prim, color, color, color);
        if (i < 2) {
            shade += 4;
        } else {
            shade -= 4;
        }
        angle += 0x100;
        prim->x2 = prim->x3 = quad->x + ((quad->radius * rcos(angle)) >> 12);
        prim->y2            = 0;
        prim->y3            = quad->y + ((quad->radius * rsin(angle)) >> 13);
        color               = shade;
        if (shade >= 0x100) {
            color = 0xFF;
        }
        if (shade < 0) {
            color = 0;
        }
        setRGB2(prim, color, color, color);
        setRGB3(prim, color, color, color);
        Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(POLY_G4));
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), NULL);
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
}
