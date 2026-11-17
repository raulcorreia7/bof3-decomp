#include "area082_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2F50(Pos3* pos, s16 radius_a, s16 radius_b, u16 angle_b, s32 shade_a, s32 shade_b) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* prim;
    u16      angle;
    u16      next;
    u16      other;
    s32      frame_parity;
    s16      i;

    Area_SetCameraMatrix(&camera);
    Area_ProjectPoint((s32*)pos, &screen);
    size.vx = radius_a;
    size.vy = radius_b;
    Game_ProjectWorldPoint(pos, &size, &scale);

    frame_parity = g_FrameCount & 1;
    scale.vx += frame_parity;
    scale.vy += frame_parity;

    angle = 0;
    i     = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        next  = angle + (ONE / 16);
        other = angle_b + (ONE / 16);
        setXY0(prim, screen.vx, screen.vy);
        prim->x1 = (s16)(screen.vx + FIXED_MUL(scale.vx, rcos(angle)));
        prim->y1 = (s16)(screen.vy + FIXED_MUL(scale.vx, rsin(angle)));
        prim->x2 = (s16)(screen.vx + FIXED_MUL(scale.vy, rcos(other)));
        prim->y2 = (s16)(screen.vy + FIXED_MUL(scale.vy, rsin(other)));
        if (frame_parity != 0) {
            setRGB0(prim, shade_a, shade_a, shade_a);
        } else {
            setRGB0(prim, 0, 0, 0);
        }
        setRGB1(prim, shade_b, shade_b, shade_b);
        setRGB2(prim, shade_b, shade_b, shade_b);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
        angle = next;
        i++;
    } while ((u16)i < 16);
}
#else
INCLUDE_ASM(func_801F2F50);
#endif
