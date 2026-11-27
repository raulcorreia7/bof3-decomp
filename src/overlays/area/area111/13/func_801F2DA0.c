#include "area111_13.h"

/* Draws a band of 32 semi-transparent Gouraud quads between the rings of the
 * two radii around the position, alternating the shade at the two edges. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F2DA0(void* position, s32 radius1, s32 radius2) {
    VECTOR   point;
    VECTOR   last;
    DVECTOR  inner;
    DVECTOR  outer;
    MATRIX   camera;
    u8       scratch[32]; /* retail reserves 32 frame bytes past the matrix; no statement uses them */
    POLY_G4* prim;
    s32*     pos;
    s32      turn;
    u8       i;
    u16      angle;
    s32      sine;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    Camera_SetMatrix(&camera);
    pos      = position;
    point.vx = pos[0];
    point.vy = pos[1] + (((s16)radius1 * rcos(0)) >> 4);
    point.vz = pos[2] + (((s16)radius1 * rsin(0)) << 4);
    Camera_ProjectPoint((s32*)&point, &inner);
    point.vy = pos[1] + (((s16)radius2 * rcos(0)) >> 4);
    point.vz = pos[2] + (((s16)radius2 * rsin(0)) << 4);
    Camera_ProjectPoint((s32*)&point, &outer);
    turn = 0;

    for (i = 0; i < 32;) {
        last = point;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100), 0);
        Area_CellAddPrim(last.vx, last.vy, 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY2(prim, inner.vx, inner.vy, outer.vx, outer.vy);
        turn += ONE / 32;
        angle    = turn;
        point.vx = pos[0];
        point.vy = pos[1] + (((s16)radius1 * rcos(angle)) >> 4);
        point.vz = pos[2] + (((s16)radius1 * rsin(angle)) << 4);
        Camera_ProjectPoint((s32*)&point, &inner);
        point.vy = pos[1] + (((s16)radius2 * rcos(angle)) >> 4);
        sine     = (s16)radius2 * rsin(angle);
        ++i;
        /* FAKE: keeps the segment step beside the second radius (54 rows with plain C). */
        FAKE_BARRIER();
        point.vz = pos[2] + (sine << 4);
        Camera_ProjectPoint((s32*)&point, &outer);
        prim->x2 = inner.vx;
        prim->y2 = inner.vy;
        prim->x3 = outer.vx;
        prim->y3 = outer.vy;
        setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
        setRGB3(prim, 0, 0, 0);
        Area_CellAddPrim(last.vx, last.vy, 0, sizeof(POLY_G4));
    }
}
#else
INCLUDE_ASM(func_801F2DA0);
#endif
