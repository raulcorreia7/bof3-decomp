#include "area041_13.h"

MATCH void func_801F34AC(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    u16*      sxy;
    long      p;
    long      flag;
    s32       i;

    if (D_801F4334[SELF(Actor)->timer] != 0) {
        func_801F387C(D_801F4334[SELF(Actor)->timer] << 4);
    } else {
        func_801F3704();
    }

    quad = g_ScratchPadVectors;
    sxy  = (u16*)D_1F800034;
    for (i = 0; i < 0xE; i += 2) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        setVector(quad, SELF(Actor)->pos.x.fixed + D_801F4344[i] * 0x80 + (s8)D_801F4354[i] * SELF(Actor)->timer * 8,
                  SELF(Actor)->pos.y.fixed + D_801F4344[i + 1] * 0x80 + (s8)D_801F4354[i + 1] * SELF(Actor)->timer * 8, COORD_INT(SELF(Actor)->pos.z));
        RotTransPers(quad, (long*)sxy, &p, &flag);
        prim->x0 = prim->x2 = sxy[0] - SELF(Actor)->timer;
        prim->y0 = prim->y1 = SPAD(0)->unk_34[1] - SELF(Actor)->timer;
        prim->x1 = prim->x3 = sxy[0] + SELF(Actor)->timer;
        prim->y2 = prim->y3 = SPAD(0)->unk_34[1] + SELF(Actor)->timer;
        Area_ApplyTileToQuad(((0xD - SELF(Actor)->timer) << 19) + ((0xBA00u << 16) | 0x9124u), prim, 1);
        Area_CellAddPrim((SELF(Actor)->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (SELF(Actor)->pos.y.fixed + AREA_CELL_ORIGIN) << 9, 6, sizeof(POLY_FT4));
    }

    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 0xE) {
        SELF(Actor)->header.step += 1;
    }
}
