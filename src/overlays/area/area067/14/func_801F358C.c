#include "area067_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F358C(AreaRippleQuad* quad) {
    POLY_G4* prim;
    s16      ring;
    s16      next;
    u16      angle;
    u16      next_angle;
    u8       i;
    u8       j;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 0x380, 0x100), NULL);
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
    i = 0;
    do {
        ring       = (quad->radius * i) / 8;
        next       = (quad->radius * (i + 1)) / 8;
        angle      = quad->height - i * 0x80;
        next_angle = quad->height - (i + 1) * 0x80;
        j          = 0;
        do {
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            prim->x0 = quad->x + ((ring * rcos(angle)) >> 12);
            prim->y0 = quad->y + ((ring * rsin(angle)) >> 13);
            prim->x1 = quad->x + ((next * rcos(next_angle)) >> 12);
            prim->y1 = quad->y + ((next * rsin(next_angle)) >> 13);
            angle += 0x100;
            prim->x2 = quad->x + ((ring * rcos(angle)) >> 12);
            prim->y2 = quad->y + ((ring * rsin(angle)) >> 13);
            next_angle += 0x100;
            prim->x3 = quad->x + ((next * rcos(next_angle)) >> 12);
            prim->y3 = quad->y + ((next * rsin(next_angle)) >> 13);
            setRGB0(prim, 0, 0, 0);
            setRGB1(prim, 0, 0, 0);
            setRGB2(prim, 0x40, 0x40, 0x40);
            setRGB3(prim, 0x40, 0x40, 0x40);
            Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(POLY_G4));
            j++;
        } while (j < 16);
        i++;
    } while (i < 8);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), NULL);
    Area_AddCellPrim(D_801F53A0, D_801F53A4, 4, sizeof(DR_MODE));
}
#else
INCLUDE_ASM(func_801F358C);
#endif
