#include "area145_14.h"

/* Draws a semi-transparent fan of eight Gouraud triangles from (x, y) around the radius, one per 0x100 of the angle. */
MATCH void func_801F34C8(s16 x, s16 y, s16 radius, u16 angle) {
    POLY_G3* packet;
    u8       i;

    i = 0;
    do {
        packet = GFX_BeginPolyG3(1);
        setXY2(packet, x, y, (s16)(x + FIXED_MUL(radius, rcos(angle))), (s16)(y + FIXED_MUL(radius, rsin(angle))));
        angle += 0x100;
        packet->x2 = (s16)(x + FIXED_MUL(radius, rcos(angle)));
        i += 1;
        packet->y2 = (s16)(y + FIXED_MUL(radius, rsin(angle)));
        setRGB0(packet, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, 0);
        setRGB1(packet, 0, 0, 0);
        setRGB2(packet, 0, 0, 0);
        GFX_AddPrim(1u, sizeof(POLY_G3));
    } while (i < 8);
}
