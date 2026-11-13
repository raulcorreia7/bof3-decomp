#include "area111_13.h"

/* Draw the Tidal Caves entrance trail: one textured quad over the actor's cell, queued with its
 * draw mode. */
MATCH void func_801F3244(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    SVECTOR*  corner1;
    SVECTOR*  corner2;
    SVECTOR*  corner3;
    long      depth;
    long      flag;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 0, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);

    quad     = D_1F800014;
    corner1  = quad + 1;
    corner2  = quad + 2;
    corner3  = quad + 3;
    quad->vx = corner2->vx = g_Task->screen_y - 0x37C0;
    corner1->vx = corner3->vx = g_Task->screen_y - 0x36C0;
    quad->vy = corner1->vy = corner2->vy = corner3->vy = 0x16C0;
    quad->vz = corner1->vz = 0x140;
    corner2->vz = corner3->vz = 0x280;

    RotTransPers4(quad, corner1, corner2, corner3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);

    func_80155560((0x2378u << 16) | 0x013Du, prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_FT4));
}
