#include "area174_13.h"

/* Draws a shot's ground ring: sixteen Gouraud wedges around the projected point, each
 * corner on the ellipse the two radii span, rotated by the given angle. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F2FEC(s32* pos, s16 radius_x, s16 radius_y, u16 rotation, u8 center_shade, u8 rim_shade) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    POLY_G3* prim;
    u16      angle;
    s16      ellipse[2];
    MATRIX   unused;
    u8       i;
    s16      rot;
    u16      tpage;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
    rot   = rotation;
    angle = 0;
    i     = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, NULL);
    Area_CellAddPrim(pos[0], pos[1], 0, sizeof(DR_MODE));

    Camera_ProjectPoint(pos, &screen);
    size.vx = radius_x;
    size.vy = radius_y;
    Game_ProjectWorldPoint(pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    scale.vy += g_FrameCount & 1;

    do {
        prim = GFX_BeginPolyG3(1);
        setXY0(prim, screen.vx, screen.vy);
        ellipse[0] = FIXED_MUL(scale.vx, rcos(angle));
        ellipse[1] = FIXED_MUL(scale.vy, rsin(angle));
        prim->x1   = screen.vx + ((ellipse[0] * rcos(rot) - ellipse[1] * rsin(rot)) >> 12);
        prim->y1   = screen.vy + ((ellipse[0] * rsin(rot) + ellipse[1] * rcos(rot)) >> 12);
        angle += ONE / 16;
        ellipse[0] = FIXED_MUL(scale.vx, rcos(angle));
        ellipse[1] = FIXED_MUL(scale.vy, rsin(angle));
        prim->x2   = screen.vx + ((ellipse[0] * rcos(rot) - ellipse[1] * rsin(rot)) >> 12);
        prim->y2   = screen.vy + ((ellipse[0] * rsin(rot) + ellipse[1] * rcos(rot)) >> 12);
        setRGB0(prim, center_shade, center_shade, center_shade);
        setRGB1(prim, rim_shade, rim_shade, rim_shade);
        setRGB2(prim, rim_shade, rim_shade, rim_shade);
        Area_CellAddPrim(pos[0], pos[1], 0, sizeof(POLY_G3));
        i++;
    } while (i < 16);
}
#else
INCLUDE_ASM(func_801F2FEC);
#endif
