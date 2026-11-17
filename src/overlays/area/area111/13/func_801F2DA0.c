#include "area111_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2DA0(void* position, s32 radius1, s32 radius2) {
    VECTOR   point;
    DVECTOR  inner;
    DVECTOR  outer;
    MATRIX   camera;
    POLY_G4* prim;
    s32*     pos;
    s32      turn;
    s32      i;
    s32      sine;
    u16      angle;

    pos = position;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));
    Area_SetCameraMatrix(&camera);
    point.vx = pos[0] + (((s16)radius1 * rcos(0)) >> 4);
    sine     = rsin(0);
    point.vy = pos[1] + (((s16)radius1 * sine) >> 4);
    point.vz = pos[2] + (((s16)radius1 * sine) << 4);
    Area_ProjectPoint(&point, &inner);
    point.vx = pos[0] + (((s16)radius2 * rcos(0)) >> 4);
    sine     = rsin(0);
    point.vy = pos[1] + (((s16)radius2 * sine) >> 4);
    point.vz = pos[2] + (((s16)radius2 * sine) << 4);
    Area_ProjectPoint(&point, &outer);
    turn = 0;
    i    = 0;
    do {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), 0);
        Area_AddCellPrim(pos[0], pos[1], 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = inner.vx;
        prim->y0 = inner.vy;
        prim->x1 = outer.vx;
        prim->y1 = outer.vy;
        turn += 0x80;
        angle    = turn;
        point.vx = pos[0] + (((s16)radius1 * rcos(angle)) >> 4);
        sine     = rsin(angle);
        point.vy = pos[1] + (((s16)radius1 * sine) >> 4);
        point.vz = pos[2] + (((s16)radius1 * sine) << 4);
        Area_ProjectPoint(&point, &inner);
        point.vx = pos[0] + (((s16)radius2 * rcos(angle)) >> 4);
        sine     = rsin(angle);
        point.vy = pos[1] + (((s16)radius2 * sine) >> 4);
        point.vz = pos[2] + (((s16)radius2 * sine) << 4);
        Area_ProjectPoint(&point, &outer);
        prim->x2 = inner.vx;
        prim->y2 = inner.vy;
        prim->x3 = outer.vx;
        prim->y3 = outer.vy;
        setRGB0(prim, 0x80, 0x80, 0x80);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0x80, 0x80, 0x80);
        setRGB3(prim, 0, 0, 0);
        Area_AddCellPrim(pos[0], pos[1], 0, sizeof(POLY_G4));
        i++;
    } while (i < 32);
}
#else
INCLUDE_ASM(func_801F2DA0);
#endif
