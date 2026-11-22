#include "area134_13.h"

MATCH void func_801F4F0C(s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y) {
    s32      point[3];
    DVECTOR  screen0;
    DVECTOR  screen1;
    POLY_F3* packet;
    s32      i;
    u8       scratch[32]; /* FAKE: unreferenced local pads frame to 0x80. */

    Camera_ProjectPoint(center, &screen0);
    point[0] = center[0] + FIXED_MUL(radius, rcos(angle));
    point[1] = center[1] + FIXED_MUL(radius, rsin(angle));
    point[2] = center[2];
    Camera_ProjectPoint(point, &screen1);

    i = 0;
    do {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 896, 256) & HALF_MASK, 0);
        Area_CellAddPrim(center[0] + offset_x, center[1] + offset_y, 0, 0x18);
        packet = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(packet);
        PSX_SET_SEMI_TRANSPARENT(packet);
        setXY2(packet, (u16)screen0.vx, (u16)screen0.vy, (u16)screen1.vx, (u16)screen1.vy);
        angle += 0x100;
        point[0] = center[0] + FIXED_MUL(radius, rcos(angle));
        point[1] = center[1] + FIXED_MUL(radius, rsin(angle));
        i += 1;
        Camera_ProjectPoint(point, &screen1);
        packet->x2 = (u16)screen1.vx;
        packet->y2 = (u16)screen1.vy;
        PSX_SET_NEUTRAL_RGB(packet);
        Area_CellAddPrim(center[0] + offset_x, center[1] + offset_y, 0, 0x18);
    } while (((i & BYTE_MASK)) < 4u);
}
