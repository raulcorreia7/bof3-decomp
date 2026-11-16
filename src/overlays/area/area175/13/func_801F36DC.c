#include "area175_13.h"

/* Draws a filled disc as a fan of 32 semi-transparent Gouraud triangles around (x, y) with the
 * given radius; the centre corner is white and the rim black. */
MATCH void func_801F36DC(s16 x, s16 y, s16 radius) {
    POLY_G3* packet;
    s32      angle;
    s32      next;
    s32      other;
    s32      scale;

    GFX_AddDitheredDrawMode(1u, GetTPage(0, 1, 0x3C0, 0) & HALF_MASK);
    angle = 0;
    do {
        packet = GFX_BeginPolyG3(1);
        next   = angle + 128;
        other  = (u16)next;
        setXY2(packet, x, y, (s16)(x + ((radius * rcos((u16)angle)) >> 0x0C)), (s16)(y + ((radius * rsin((u16)angle)) >> 0x0C)));
        packet->x2 = (s16)(x + ((radius * rcos(other)) >> 0x0C));
        scale      = rsin(other);
        setRGB0(packet, 0x80, 0x80, 0x80);
        setRGB1(packet, 0, 0, 0);
        setRGB2(packet, 0, 0, 0);
        packet->y2 = (s16)(y + ((radius * scale) >> 0x0C));
        GFX_AddPrim(1u, sizeof(POLY_G3));
        angle = next;
    } while ((u16)angle < ONE);
}
