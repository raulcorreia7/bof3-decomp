#include "area103_13.h"

/* Draw a shaded disc at a world position after setting the camera matrix: the projected centre and
 * radius scale a 32-segment fan. */
MATCH void func_801F352C(s32* pos, s16 radius, u8 center_shade, u8 rim_shade) {
    DVECTOR  screen;
    Point2D  size;
    u16      projected[2];
    MATRIX   matrix;
    POLY_G3* packet;
    u16      angle;
    u16      next;
    u16      other;
    s16      screen_radius;
    s32      scale;

    Area_SetCameraMatrix(&matrix);
    Area_ProjectPoint(pos, &screen);
    size.x = radius;
    func_801AFFD8(pos, &size, projected);

    screen_radius = projected[0] + (g_FrameCount & 1);
    angle         = 0;
    do {
        packet = GFX_BeginPolyG3(1);
        next   = angle + 0x80;
        other  = next & 0xFFF;
        setXY2(packet, screen.vx, screen.vy, (s16)(screen.vx + ((screen_radius * rcos((u16)angle)) >> 0x0C)), (s16)(screen.vy + ((screen_radius * rsin((u16)angle)) >> 0x0C)));
        packet->x2 = (s16)(screen.vx + ((screen_radius * rcos((u16)other)) >> 0x0C));
        scale      = rsin((u16)other);
        packet->y2 = (s16)(screen.vy + ((screen_radius * scale) >> 0x0C));
        setRGB0(packet, center_shade, center_shade, center_shade);
        setRGB1(packet, rim_shade, rim_shade, rim_shade);
        setRGB2(packet, rim_shade, rim_shade, rim_shade);
        GFX_AddPrim(1u, sizeof(POLY_G3));
        angle = next;
    } while ((u16)angle < 0x1000);
}
