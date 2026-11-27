#include "area098_13.h"

MATCH void func_801F5050(u8 shade) {
    DVECTOR  screen0;
    DVECTOR  screen1;
    s32      point[3];
    u8       scratch[0x40];
    POLY_F4* packet;
    u8       i;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    Camera_SetMatrix(scratch);
    point[0] = SELF(Actor)->pos.x.fixed - TO_COORD(2);
    point[1] = SELF(Actor)->pos.y.fixed;
    point[2] = TO_COORD(512);
    Camera_ProjectPoint(point, &screen0);
    point[2] = TO_COORD(1280);
    Camera_ProjectPoint(point, &screen1);
    for (i = 0; i < 4;) {
        point[0] += TO_COORD(1);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
        packet = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(packet);
        SetSemiTrans(packet, 1);
        /* setXY2 written out: the step sits between its first two stores. */
        packet->x0 = screen0.vx;
        i++;
        /* FAKE: holds the counter step in the first corner load delay as retail; best pure C 2 rows. */
        FAKE_ORDER_FENCE();
        packet->y0 = screen0.vy;
        packet->x1 = screen1.vx;
        packet->y1 = screen1.vy;
        point[2]   = TO_COORD(512);
        Camera_ProjectPoint(point, &screen0);
        point[2] = TO_COORD(1280);
        Camera_ProjectPoint(point, &screen1);
        packet->x2 = screen0.vx;
        packet->y2 = screen0.vy;
        packet->x3 = screen1.vx;
        packet->y3 = screen1.vy;
        setRGB0(packet, shade, shade, shade);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(POLY_F4));
    }
}
