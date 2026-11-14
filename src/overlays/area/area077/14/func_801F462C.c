#include "area077_14.h"

/* Draw a shaded disc at a world position: the projected centre and radius scale a 32-segment fan. */
MATCH void func_801F462C(s32* pos, s16 radius, u8 center_shade, u8 rim_shade) {
    DVECTOR  screen;
    Point2s  size;
    Point2u projected;
    POLY_G3* packet;
    u16      angle;
    u16      next;
    u16      other;
    s16      screen_radius;
    s32      scale;

    Area_ProjectPoint(pos, &screen);
    size.x = radius;
    Game_ProjectWorldPoint(pos, &size, &projected);

    screen_radius = projected.x + (g_FrameCount & 1);
    angle         = 0;
    do {
        packet = GFX_BeginPolyG3(1);
        next   = angle + ONE / 32;
        other  = next & ANGLE_MASK;
        setXY2(packet, screen.vx, screen.vy, (s16)(screen.vx + (FIXED_MUL(screen_radius, rcos(angle)))), (s16)(screen.vy + (FIXED_MUL(screen_radius, rsin(angle)))));
        packet->x2 = (s16)(screen.vx + (FIXED_MUL(screen_radius, rcos(other))));
        scale      = rsin(other);
        packet->y2 = (s16)(screen.vy + (FIXED_MUL(screen_radius, scale)));
        setRGB0(packet, center_shade, center_shade, center_shade);
        setRGB1(packet, rim_shade, rim_shade, rim_shade);
        setRGB2(packet, rim_shade, rim_shade, rim_shade);
        GFX_AddPrim(1u, sizeof(POLY_G3));
        angle = next;
    } while ((u16)angle < ONE);
}
