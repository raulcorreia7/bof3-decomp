#ifndef OVERLAY_BMAGIC_MAGIC172_03_H
#define OVERLAY_BMAGIC_MAGIC172_03_H

/* The bmagic/magic172/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect timer drops by 2 per tick. */
#define EFFECT_TIMER_TICK 2

extern Callback D_801F0B90[];

extern BMagicRingShade D_801F0B9C[];

void            func_800AF3A0(VECTOR pos, s16 step);
void            func_801EEDD8(void);
void            func_801EF7CC(void);
void            func_801EFA2C(void);
void            func_801EFD04(void);
void            func_801EFFE8(void);
void            func_801F02C8(s32 angle, s32 spread);
void            func_801F05E8(s32 angle, s32 spread);
extern Callback D_801F0B7C[];
void            func_801F0908(void);

/* Draws one jagged line out from the effect cell at ANGLE: each segment turns by up to WOBBLE and grows by a
 * random share of SPREAD; before step 3 the shade falls with the length past FADE, and the line ends once it is
 * shorter than MIN. A statement macro: the member declares LINE_G2* prim, u16 x and y, and s32 i, sine and tpage. */
#define MAGIC172_DRAW_JAGGED_LINE(ANGLE, SPREAD, WOBBLE, FADE, MIN)                                                                 \
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;                                                               \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                         \
    GFX_AddPrim(3, sizeof(DR_MODE));                                                                                                \
    D_1F800000.view.effect.params[0] = 16;                                                                                          \
    D_1F800000.view.effect.params[2] = ANGLE;                                                                                       \
    x                                = g_Task->unk_2E.half;                                                                         \
    y                                = g_Task->unk_30.half;                                                                         \
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 6;                                                                          \
    i                                = 1;                                                                                           \
    do {                                                                                                                            \
        prim = (LINE_G2*)g_GfxPrimCursor;                                                                                           \
        SetLineG2(prim);                                                                                                            \
        SetSemiTrans(prim, 1);                                                                                                      \
        prim->x0                         = x + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
        prim->y0                         = y + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
        D_1F800000.view.effect.params[1] = (i & 0x1F) << 7;                                                                         \
        sine                             = rsin(D_1F800000.view.effect.params[1]);                                                  \
        D_1F800000.view.effect.params[0] += FIXED_MUL(sine, rand() & (s16)SPREAD);                                                  \
        D_1F800000.view.effect.params[2] = (D_1F800000.view.effect.params[2] + (rand() & WOBBLE)) & 0xFFF;                          \
        prim->x1                         = x + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
        prim->y1                         = y + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
        if (g_Task->header.step < 3) {                                                                                              \
            D_1F800000.view.effect.params[3] = (D_1F800000.view.effect.params[0] - FADE) * 6;                                       \
        }                                                                                                                           \
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3] / 3);    \
        if (g_Task->header.step < 3) {                                                                                              \
            D_1F800000.view.effect.params[3] = (D_1F800000.view.effect.params[0] - (FADE + 1)) * 6;                                 \
        }                                                                                                                           \
        setRGB1(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3] / 3);    \
        GFX_AddPrim(3, sizeof(LINE_G2));                                                                                            \
        i++;                                                                                                                        \
    } while (D_1F800000.view.effect.params[0] >= MIN);

#endif
