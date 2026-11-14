#ifndef OVERLAY_BMAGIC_MAGIC013_03_H
#define OVERLAY_BMAGIC_MAGIC013_03_H

/* The bmagic/magic013/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Magic010SharedSteps D_801EEC04;

extern s32 D_1F800004;

extern Callback     D_801F03C0[];
extern Callback     D_801F03DC[];
extern u8           D_801F03D4[];
extern SVECTOR      D_1F800014[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F03E4[];
#define BMAGIC_EFFECT_SLOTS D_801F03E4
#define BMAGIC_EFFECT_COUNT 64
s32  func_800AED5C(s32 arg0, u32 battler_index);
void func_801EF79C(void);
void func_801EF648(void);
void func_801EFAA8(void);
void func_801EFDB4(void);
void func_801F0164(void);

/* The wave band scratch: the wave height, the facing angle and the band shade, then the quad corners (D_1F800014). */
#define WAVE_HEIGHT D_1F800000.view.scenario.math_00
#define WAVE_ANGLE  D_1F800000.view.scenario.math_04
#define WAVE_SHADE  D_1F800000.view.scenario.math_08

/* Draws the wave band of 16 shaded quads around the effect cell, turned by the facing table; LIFT is added to the
 * band height for the first and second corners. The caller declares prim, depth, flag, i and tpage. */
#define MAGIC013_DRAW_WAVE_BAND(lift)                                                                                                                                         \
    tpage = getTPage(0, 1, 320, 256);                                                                                                                                         \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                   \
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));                                                                                           \
    WAVE_SHADE       = g_Task->unk_04 * 12;                                                                                                                                   \
    WAVE_HEIGHT      = FIXED_MUL(rsin(0), 64);                                                                                                                                \
    WAVE_ANGLE       = D_801F03D4[g_Task->facing] << 7;                                                                                                                       \
    D_1F800014[3].vx = (u32)rsin(WAVE_ANGLE) >> 5;                                                                                                                            \
    D_1F800014[3].vy = (u32)rcos(WAVE_ANGLE) >> 5;                                                                                                                            \
    D_1F800014[3].vz = FIXED_MUL(rsin(0), WAVE_HEIGHT);                                                                                                                       \
    for (i = 1; i <= 16; i++) {                                                                                                                                               \
        prim = (POLY_G4*)g_GfxPrimCursor;                                                                                                                                     \
        SetPolyG4(prim);                                                                                                                                                      \
        SetSemiTrans(prim, 1);                                                                                                                                                \
        WAVE_HEIGHT      = FIXED_MUL(rsin(i << 7), 64);                                                                                                                       \
        WAVE_ANGLE       = ((D_801F03D4[g_Task->facing] + i) & 0x1F) << 7;                                                                                                    \
        D_1F800014[0].vx = D_1F800014[3].vx;                                                                                                                                  \
        D_1F800014[0].vy = D_1F800014[3].vy;                                                                                                                                  \
        D_1F800014[0].vz = D_1F800014[3].vz + (lift);                                                                                                                         \
        D_1F800014[2].vx = D_1F800014[3].vx;                                                                                                                                  \
        D_1F800014[2].vy = D_1F800014[3].vy;                                                                                                                                  \
        D_1F800014[2].vz = D_1F800014[3].vz;                                                                                                                                  \
        D_1F800014[3].vx = (u32)rsin(WAVE_ANGLE) >> 5;                                                                                                                        \
        D_1F800014[3].vy = (u32)rcos(WAVE_ANGLE) >> 5;                                                                                                                        \
        D_1F800014[3].vz = FIXED_MUL(rsin((i & 3) << 10), WAVE_HEIGHT);                                                                                                       \
        D_1F800014[1].vx = D_1F800014[3].vx;                                                                                                                                  \
        D_1F800014[1].vy = D_1F800014[3].vy;                                                                                                                                  \
        D_1F800014[1].vz = D_1F800014[3].vz + (lift);                                                                                                                         \
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag); \
        setRGB0(prim, 1, 1, 1);                                                                                                                                               \
        setRGB1(prim, 1, 1, 1);                                                                                                                                               \
        setRGB2(prim, WAVE_SHADE, WAVE_SHADE, WAVE_SHADE);                                                                                                                    \
        setRGB3(prim, WAVE_SHADE, WAVE_SHADE, WAVE_SHADE);                                                                                                                    \
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));                                                                                       \
    }

#endif
