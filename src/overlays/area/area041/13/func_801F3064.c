#include "area041_13.h"

/* Draw the actor's sprite quad: its four corners are projected into one textured primitive and the
 * cell is queued with its draw mode. */
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

    quad     = D_1F800014;
    corner1  = quad + 1;
    corner2  = quad + 2;
    corner3  = quad + 3;
    quad->vx = corner1->vx = g_Task->pos.x.fixed + 0x10;
    corner2->vx = corner3->vx = g_Task->pos.x.fixed + 0x10;
    quad->vy = corner2->vy = g_Task->pos.y.fixed + 0x100;
    corner1->vy = corner3->vy = g_Task->pos.y.fixed + 0x80;
    quad->vz = corner1->vz = -0x160;
    corner2->vz = corner3->vz = -0xE0;

    RotTransPers4(quad, corner1, corner2, corner3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    func_80155560(0xBD5000F9, prim, 1);
    Area_AddCellPrim((g_Task->pos.x.fixed + 0x4000) << 9, (g_Task->pos.y.fixed + 0x40C0) << 9, 1, sizeof(POLY_FT4));
}
