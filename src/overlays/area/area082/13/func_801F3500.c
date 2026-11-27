#include "area082_13.h"

/* Draws a pillar of light at the task's position: sixteen semi-transparent Gouraud quads between a ring at the
 * task's radius and the same ring raised by the task's screen_y, with a shade that alternates each frame and
 * steps by 4 per segment. */
MATCH void func_801F3500(void) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    MATRIX   matrix;
    u8       camera[48];
    POLY_G4* prim;
    s32      angle;
    s32      shade;
    u8       i;

    /* The camera call ignores its argument, so camera stays unused. */
    Camera_SetMatrix(&matrix);
    angle    = 0;
    point[0] = SELF(Actor)->pos.x.fixed + (((s16)SELF(Actor)->screen_x * rcos(0)) >> 4);
    point[1] = SELF(Actor)->pos.y.fixed + (((s16)SELF(Actor)->screen_x * rsin(0)) >> 4);
    point[2] = SELF(Actor)->pos.z.fixed;
    Camera_ProjectPoint(point, &inner);
    point[2] = SELF(Actor)->pos.z.fixed + TO_COORD((s16)SELF(Actor)->screen_y);
    Camera_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x20;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = SELF(Actor)->pos.x.fixed + (((s16)SELF(Actor)->screen_x * rcos((u16)angle)) >> 4);
        point[1] = SELF(Actor)->pos.y.fixed + (((s16)SELF(Actor)->screen_x * rsin((u16)angle)) >> 4);
        point[2] = SELF(Actor)->pos.z.fixed;
        Camera_ProjectPoint(point, &inner);
        point[2] = SELF(Actor)->pos.z.fixed + TO_COORD((s16)SELF(Actor)->screen_y);
        Camera_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx, outer.vy);
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, shade, shade, shade);
        if ((u8)(i - 4) >= 8) {
            shade += 4;
        } else {
            shade -= 4;
        }
        setRGB2(prim, shade, shade, shade);
        setRGB3(prim, shade, shade, shade);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(POLY_G4));
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
    }
}
