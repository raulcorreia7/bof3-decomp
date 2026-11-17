#include "area098_13.h"

/* Draws the ring of light around pos: 32 gradient quads on the second ordering
 * layer, the inner edge at orange_radius and the outer at black_radius. */
MATCH void func_801F4490(WorldPos* pos, s32 orange_radius, s32 black_radius) {
    /* kept: sce15ef1 func_801D36BC has the same body over an s32[3]; this entry point passes a WorldPos. */
    VECTOR   vertex;
    DVECTOR  inner;
    DVECTOR  outer;
    MATRIX   camera;
    POLY_G4* prim;
    u16      tpage;
    s32      turn;
    u16      angle;
    u8       i;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
    Area_SetCameraMatrix(&camera);
    vertex.vx = pos->x.fixed + (orange_radius << 4);
    vertex.vy = pos->y.fixed;
    vertex.vz = pos->z.fixed;
    Area_ProjectPoint(&vertex.vx, &inner);
    vertex.vx = pos->x.fixed + (black_radius << 4);
    Area_ProjectPoint(&vertex.vx, &outer);
    turn = 0;
    i    = 0;
    do {
        prim     = GFX_BeginPolyG4(1);
        prim->x0 = inner.vx;
        prim->y0 = inner.vy;
        prim->x1 = outer.vx;
        prim->y1 = outer.vy;
        turn += 0x80;
        angle     = turn;
        vertex.vx = pos->x.fixed + ((orange_radius * rcos(angle)) >> 8);
        vertex.vy = pos->y.fixed + ((orange_radius * rsin(angle)) >> 8);
        Area_ProjectPoint(&vertex.vx, &inner);
        vertex.vx = pos->x.fixed + ((black_radius * rcos(angle)) >> 8);
        vertex.vy = pos->y.fixed + ((black_radius * rsin(angle)) >> 8);
        Area_ProjectPoint(&vertex.vx, &outer);
        prim->x2 = inner.vx;
        prim->y2 = inner.vy;
        prim->x3 = outer.vx;
        prim->y3 = outer.vy;
        setRGB0(prim, 0xFF, 0x7F, 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0xFF, 0x7F, 0);
        setRGB3(prim, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
        i++;
    } while (i < 32);
}
