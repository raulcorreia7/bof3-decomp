#include "area047_13.h"

MATCH void func_801F2DB4(s32* pos, s16 radius, u8 center_shade, u8 rim_shade) {
    DVECTOR  screen;
    Pos2     size;
    Pos2u    projected;
    MATRIX   matrix;
    POLY_G3* prim;
    u16      angle;
    u16      next;
    u16      other;
    s16      screen_radius;

    Area_SetCameraMatrix(&matrix);
    Area_ProjectPoint(pos, &screen);
    size.x = radius;
    Game_ProjectWorldPoint(pos, &size, &projected);

    screen_radius = projected.x + ((g_FrameCount & 1) * 2);
    angle         = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        next  = angle + (ONE / 32);
        other = next & ANGLE_MASK;
        setXY0(prim, screen.vx, screen.vy);
        prim->x1 = (s16)(screen.vx + FIXED_MUL(screen_radius, rcos(angle)));
        prim->y1 = (s16)(screen.vy + FIXED_MUL(screen_radius, rsin(angle)));
        prim->x2 = (s16)(screen.vx + FIXED_MUL(screen_radius, rcos(other)));
        prim->y2 = (s16)(screen.vy + FIXED_MUL(screen_radius, rsin(other)));
        setRGB0(prim, center_shade, center_shade, center_shade);
        setRGB1(prim, rim_shade, rim_shade, rim_shade);
        setRGB2(prim, rim_shade, rim_shade, rim_shade);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
        angle = next;
    } while ((u16)angle < ONE);
}
