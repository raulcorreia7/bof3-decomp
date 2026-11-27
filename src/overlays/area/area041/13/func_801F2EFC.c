#include "area041_13.h"

/* Draw the actor's two-row sprite quad and queue each row's cell. */
MATCH void func_801F2EFC(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    s32       i;
    long      depth;
    long      flag;

    i    = 0;
    quad = g_ScratchPadVectors;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad[0].vx = quad[1].vx = quad[2].vx = quad[3].vx = SELF(Actor)->pos.x.fixed;
        quad[0].vy = quad[2].vy = SELF(Actor)->pos.y.fixed + ((i + 1) << 7);
        quad[1].vy = quad[3].vy = SELF(Actor)->pos.y.fixed + (i << 7);
        quad[0].vz = quad[1].vz = -0x200;
        quad[2].vz = quad[3].vz = -0x80;

        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_ApplyTileToQuad(D_801F42D4[i], prim, 1);
        Area_CellAddPrim((SELF(Actor)->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (SELF(Actor)->pos.y.fixed + (i << 7) + (AREA_CELL_ORIGIN + AREA_CELL_HALF)) << 9, 1, sizeof(POLY_FT4));
        i++;
    } while (i < 2);
}
