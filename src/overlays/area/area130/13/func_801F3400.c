#include "area130_13.h"

/* Draws a 32-wedge triangle fan around the screen point, alternating red and white with the frame
 * clock, and files it into the actor's cell. */
MATCH void func_801F3400(s16 x, s16 y, s16 radius_x, s16 radius_y) {
    POLY_F3* prim;
    Pos2u    point;
    u16      angle;
    u16      i;

    angle   = 0;
    point.x = (radius_x * rcos(angle)) >> 12;
    point.y = (radius_y * rsin(angle)) >> 12;
    i       = 0;
    do {
        prim = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(prim);
        angle += 128;
        setXY2(prim, x, y, x + point.x, y + point.y);
        point.x  = (radius_x * rcos(angle)) >> 12;
        point.y  = (radius_y * rsin(angle)) >> 12;
        prim->x2 = x + point.x;
        prim->y2 = y + point.y;
        if (((g_FrameCount >> 2) & 1) != (i & 1)) {
            setRGB0(prim, 255, 0, 0);
        } else {
            setRGB0(prim, 255, 255, 255);
        }
        i += 1;
        Area_CellAddPrim(g_Actors[2].pos.x.fixed, g_Actors[2].pos.y.fixed, 12, sizeof(POLY_F3));
    } while (i < 32);
}
