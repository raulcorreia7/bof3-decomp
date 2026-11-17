#ifndef OVERLAY_BMAGIC_MAGIC172_03_H
#define OVERLAY_BMAGIC_MAGIC172_03_H

/* The bmagic/magic172/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect timer drops by 2 per tick. */
#define EFFECT_TIMER_TICK 2

extern Callback D_801F0B90[];

extern BMagicTint D_801F0B9C[];

/* func_800AF3A0 */
void            Battle_StepRangeToward(VECTOR pos, s16 step);
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
#define MAGIC172_DRAW_JAGGED_LINE(ANGLE, SPREAD, WOBBLE, FADE, MIN)                                                                                                                     \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);                                                                                                                        \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                             \
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MODE));                                                                                                                           \
    g_ScratchPad.cells.halves[0] = 16;                                                                                                                                                  \
    g_ScratchPad.cells.halves[2] = ANGLE;                                                                                                                                               \
    x                            = g_Task->unk_2E.value;                                                                                                                                \
    y                            = g_Task->unk_30.value;                                                                                                                                \
    g_ScratchPad.cells.halves[3] = g_Task->unk_09 * 6;                                                                                                                                  \
    i                            = 1;                                                                                                                                                   \
    do {                                                                                                                                                                                \
        prim = (LINE_G2*)g_GfxPrimCursor;                                                                                                                                               \
        SetLineG2(prim);                                                                                                                                                                \
        SetSemiTrans(prim, 1);                                                                                                                                                          \
        setXY0(prim, x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]), y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0])); \
        g_ScratchPad.cells.halves[1] = (i & 0x1F) << 7;                                                                                                                                 \
        sine                         = rsin(g_ScratchPad.cells.halves[1]);                                                                                                              \
        g_ScratchPad.cells.halves[0] += FIXED_MUL(sine, rand() & (s16)SPREAD);                                                                                                          \
        g_ScratchPad.cells.halves[2] = (g_ScratchPad.cells.halves[2] + (rand() & WOBBLE)) & 0xFFF;                                                                                      \
        prim->x1                     = x + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);                                                                 \
        prim->y1                     = y + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);                                                                 \
        if (g_Task->header.step < 3) {                                                                                                                                                  \
            g_ScratchPad.cells.halves[3] = (g_ScratchPad.cells.halves[0] - FADE) * 6;                                                                                                   \
        }                                                                                                                                                                               \
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 3);                                                                    \
        if (g_Task->header.step < 3) {                                                                                                                                                  \
            g_ScratchPad.cells.halves[3] = (g_ScratchPad.cells.halves[0] - (FADE + 1)) * 6;                                                                                             \
        }                                                                                                                                                                               \
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 3);                                                                    \
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));                                                                                                                       \
        i++;                                                                                                                                                                            \
    } while (g_ScratchPad.cells.halves[0] >= MIN);

#endif
