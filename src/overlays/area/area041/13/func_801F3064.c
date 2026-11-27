#include "area041_13.h"

/* Draw the actor's sprite quad from its four projected corners and queue its cell. */
MATCH void func_801F3064(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    SVECTOR*  corner1;
    SVECTOR*  corner2;
    SVECTOR*  corner3;
    long      depth;
    long      flag;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);

    quad     = g_ScratchPadVectors;
    corner1  = quad + 1;
    corner2  = quad + 2;
    corner3  = quad + 3;
    quad->vx = corner1->vx = SELF(Actor)->pos.x.fixed + 0x10;
    corner2->vx = corner3->vx = SELF(Actor)->pos.x.fixed + 0x10;
    quad->vy = corner2->vy = SELF(Actor)->pos.y.fixed + 0x100;
    corner1->vy = corner3->vy = SELF(Actor)->pos.y.fixed + 0x80;
    quad->vz = corner1->vz = -0x160;
    corner2->vz = corner3->vz = -0xE0;

    RotTransPers4(quad, corner1, corner2, corner3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad((0xBD50u << 16) | 0x00F9u, prim, 1);
    Area_CellAddPrim((SELF(Actor)->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (SELF(Actor)->pos.y.fixed + 0x40C0) << 9, 1, sizeof(POLY_FT4));
}
