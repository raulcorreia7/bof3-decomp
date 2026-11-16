#include "area098_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5050(u8 shade) {
    DVECTOR  screen0;
    DVECTOR  screen1;
    s32      point[3];
    u8       scratch[0x40];
    POLY_F4* packet;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    Area_SetCameraMatrix(scratch);
    point[0] = g_Task->pos.x.fixed - TO_COORD(2);
    point[1] = g_Task->pos.y.fixed;
    point[2] = TO_COORD(512);
    Area_ProjectPoint(point, &screen0);
    point[2] = TO_COORD(1280);
    Area_ProjectPoint(point, &screen1);
    for (i = 0; i < 4; i++) {
        point[0] += TO_COORD(1);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK, 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
        packet = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(packet);
        SetSemiTrans(packet, 1);
        packet->x0 = screen0.vx;
        packet->y0 = screen0.vy;
        packet->x1 = screen1.vx;
        packet->y1 = screen1.vy;
        point[2]   = TO_COORD(512);
        Area_ProjectPoint(point, &screen0);
        point[2] = TO_COORD(1280);
        Area_ProjectPoint(point, &screen1);
        packet->x2 = screen0.vx;
        packet->y2 = screen0.vy;
        packet->x3 = screen1.vx;
        packet->y3 = screen1.vy;
        packet->r0 = shade;
        packet->g0 = shade;
        packet->b0 = shade;
        Area_AddCellPrim(point[0], point[1], 0, sizeof(POLY_F4));
    }
}
#else
INCLUDE_ASM(func_801F5050);
#endif
