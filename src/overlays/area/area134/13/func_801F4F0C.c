#include "area134_13.h"

MATCH void func_801F4F0C(const s32* center, s32 radius, u16 angle, s32 offset_x, s32 offset_y) {
    s32      point[3];
    u16      screen0[2];
    u16      screen1[2];
    POLY_F3* packet;
    s32      i;
    u8       scratch[0x20]; /* FAKE: unreferenced local pads frame to 0x80. */

    Area_ProjectPoint(center, screen0);
    point[0] = ((s32*)center)[0] + ((radius * rcos(angle)) >> 12);
    point[1] = ((s32*)center)[1] + ((radius * rsin(angle)) >> 12);
    point[2] = ((s32*)center)[2];
    Area_ProjectPoint(point, screen1);

    i = 0;
    do {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 2, 896, 256) & HALF_MASK, 0);
        Area_AddCellPrim(((s32*)center)[0] + offset_x, ((s32*)center)[1] + offset_y, 0, 0x18);
        packet = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(packet);
        SetSemiTrans(packet, 1);
        packet->x0 = screen0[0];
        packet->y0 = screen0[1];
        packet->x1 = screen1[0];
        packet->y1 = screen1[1];
        angle += 0x100;
        point[0] = ((s32*)center)[0] + ((radius * rcos(angle)) >> 12);
        point[1] = ((s32*)center)[1] + ((radius * rsin(angle)) >> 12);
        i += 1;
        Area_ProjectPoint(point, screen1);
        packet->x2 = screen1[0];
        packet->y2 = screen1[1];
        setRGB0(packet, 128, 128, 128);
        Area_AddCellPrim(((s32*)center)[0] + offset_x, ((s32*)center)[1] + offset_y, 0, 0x18);
    } while (((i & BYTE_MASK)) < 4u);
}
