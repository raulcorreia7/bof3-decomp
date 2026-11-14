#include "area145_14.h"

MATCH void func_801F311C(s16 x0, s16 y0, s16 x1, s16 y1) {
    VECTOR   normal;
    POLY_G4* prim;

    setVector(&normal, y0 - y1, x1 - x0, 0);
    VectorNormal(&normal, &normal);
    normal.vx = (normal.vx * 5) >> 12;
    normal.vy = (normal.vy * 5) >> 12;
    prim      = GFX_CURSOR(POLY_G4);
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, x0, y0, x0 + normal.vx, y0 + normal.vy, x1, y1, x1 + normal.vx, y1 + normal.vy);
    setRGB0(prim, 64, 64, 64);
    setRGB1(prim, 0, 0, 0);
    setRGB2(prim, 64, 64, 64);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(1, sizeof(POLY_G4));
    prim     = GFX_CURSOR(POLY_G4);
    /* The second quad starts as the first with the other side of the normal. */
    prim[0]  = prim[-1];
    prim->x1 = x0 - normal.vx;
    prim->y1 = y0 - normal.vy;
    prim->x3 = x1 - normal.vx;
    prim->y3 = y1 - normal.vy;
    GFX_AddPrim(1, sizeof(POLY_G4));
}
