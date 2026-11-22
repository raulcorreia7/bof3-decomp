#include "area174_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FEC(s32* pos, s16 radius_a, s16 radius_b, u16 angle_b, u8 center_shade, u8 rim_shade) {
    DVECTOR  screen;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* prim;
    u16      angle;
    u16      other;
    s16      i;
    s32      tpage;

    tpage = GetTPage(0, 1, 0x3C0, 0);
    GFX_SET_DRAW_MODE(tpage);
    Area_CellAddPrim(pos[0], pos[1], 0, 0xC);

    Camera_ProjectPoint((s32*)pos, &screen);
    size.vx = radius_a;
    size.vy = radius_b;
    Camera_SetMatrix(&camera);
    Game_ProjectWorldPoint(pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    scale.vy += g_FrameCount & 1;

    angle = 0;
    i     = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, screen.vx, screen.vy);
        other    = angle_b + (ONE / 16);
        prim->x1 = (s16)(screen.vx + FIXED_MUL(scale.vx, rcos(angle)));
        prim->y1 = (s16)(screen.vy + FIXED_MUL(scale.vx, rsin(angle)));
        prim->x2 = (s16)(screen.vx + FIXED_MUL(scale.vy, rcos(other)));
        prim->y2 = (s16)(screen.vy + FIXED_MUL(scale.vy, rsin(other)));
        setRGB0(prim, center_shade, center_shade, center_shade);
        setRGB1(prim, rim_shade, rim_shade, rim_shade);
        setRGB2(prim, rim_shade, rim_shade, rim_shade);
        Area_CellAddPrim(pos[0], pos[1], 0, sizeof(POLY_G3));
        angle = other;
        i++;
    } while ((u16)i < 16);
}
#else
INCLUDE_ASM(func_801F2FEC);
#endif
