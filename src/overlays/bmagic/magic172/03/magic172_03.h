#ifndef OVERLAY_BMAGIC_MAGIC172_03_H
#define OVERLAY_BMAGIC_MAGIC172_03_H

/* The bmagic/magic172/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Effect_TickOnTimerZero lowers the counter (byte 0x09) by 2 per frame. */
#define EFFECT_TIMER_TICK 2

/* D_801F0B7C */
extern Callback   g_BMagicMagicBallCoreSteps[];
/* D_801F0B90 */
extern Callback   g_BMagicMagicBallTrailSteps[];
/* D_801F0B9C */
extern BMagicTint g_BMagicMagicBallTrailTints[];

/* func_800AF3A0 */
void Battle_StepRangeToward(VECTOR pos, s16 step);
/* func_801EEC5C */
void BMagic_MagicBallInit(void);
/* func_801EF7CC */
void BMagic_MagicBallDrawDisc(void);
/* func_801EFA2C */
void BMagic_MagicBallDrawRing(void);
/* func_801EFD04 */
void BMagic_MagicBallDrawWaveInner(void);
/* func_801EFFE8 */
void BMagic_MagicBallDrawWaveOuter(void);
/* func_801F02C8 */
void BMagic_MagicBallDrawBoltWide(s32 angle, s32 spread);
/* func_801F05E8 */
void BMagic_MagicBallDrawBoltNarrow(s32 angle, s32 spread);
/* func_801F0908 */
void BMagic_MagicBallDrawTrail(void);

/* Draws one jagged line out from the effect cell at ANGLE: each segment turns by up to WOBBLE and grows by a
 * random share of SPREAD; before step 3 the shade falls with the length past FADE, and the line ends once it is
 * shorter than MIN. A statement macro: the member declares LINE_G2* prim, u16 x and y, and s32 i, sine and tpage. */
#define MAGIC172_DRAW_JAGGED_LINE(ANGLE, SPREAD, WOBBLE, FADE, MIN)                                                                                                                     \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);                                                                                                                        \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                             \
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MODE));                                                                                                                           \
    g_ScratchPad.cells.halves[0] = 16;                                                                                                                                                  \
    g_ScratchPad.cells.halves[2] = ANGLE;                                                                                                                                               \
    x                            = SELF(PartyMember)->screen_x.value;                                                                                                                   \
    y                            = SELF(PartyMember)->screen_y.value;                                                                                                                   \
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 6;                                                                                                                       \
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
        if (SELF(PartyMember)->header.step < 3) {                                                                                                                                       \
            g_ScratchPad.cells.halves[3] = (g_ScratchPad.cells.halves[0] - FADE) * 6;                                                                                                   \
        }                                                                                                                                                                               \
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 3);                                                                    \
        if (SELF(PartyMember)->header.step < 3) {                                                                                                                                       \
            g_ScratchPad.cells.halves[3] = (g_ScratchPad.cells.halves[0] - (FADE + 1)) * 6;                                                                                             \
        }                                                                                                                                                                               \
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 3);                                                                    \
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_G2));                                                                                                                       \
        i++;                                                                                                                                                                            \
    } while (g_ScratchPad.cells.halves[0] >= MIN);

#endif
