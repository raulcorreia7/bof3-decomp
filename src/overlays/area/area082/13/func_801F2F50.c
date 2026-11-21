#include "area082_13.h"

/* Draws one shaded ring of 16 triangles around pos, rotated by angle_b. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F2F50(Pos3* pos, s16 radius_a, s16 radius_b, u16 angle_b, s32 shade_a, s32 shade_b) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    DVECTOR  rot;
    MATRIX   camera;
    POLY_G3* prim;
    u16      angle;
    u8       phase;
    u8       i;

    Camera_SetMatrix(&camera);
    Camera_ProjectPoint((s32*)pos, &screen);
    size.vx = radius_a;
    size.vy = radius_b;
    Game_ProjectWorldPoint(pos, &size, &scale);
    phase = g_FrameCount & 1;
    scale.vx += phase;
    scale.vy += phase;
    angle = 0;
    i     = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = screen.vx;
        prim->y0 = screen.vy;
        rot.vx   = (scale.vx * rcos(angle)) >> 12;
        rot.vy   = (scale.vy * rsin(angle)) >> 12;
        prim->x1 = screen.vx + ((rot.vx * rcos(angle_b) - rot.vy * rsin(angle_b)) >> 12);
        prim->y1 = screen.vy + ((rot.vx * rsin(angle_b) + rot.vy * rcos(angle_b)) >> 12);
        angle += ONE / 16;
        rot.vx   = (scale.vx * rcos(angle)) >> 12;
        rot.vy   = (scale.vy * rsin(angle)) >> 12;
        prim->x2 = screen.vx + ((rot.vx * rcos(angle_b) - rot.vy * rsin(angle_b)) >> 12);
        prim->y2 = screen.vy + ((rot.vx * rsin(angle_b) + rot.vy * rcos(angle_b)) >> 12);
        setRGB0(prim, shade_a, shade_a, phase ? shade_a : 0);
        setRGB1(prim, shade_b, shade_b, phase ? shade_b : 0);
        setRGB2(prim, shade_b, shade_b, phase ? shade_b : 0);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
        i++;
    } while (i < 16);
}
#else
INCLUDE_ASM(func_801F2F50);
#endif
