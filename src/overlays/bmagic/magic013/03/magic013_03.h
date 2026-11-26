#ifndef OVERLAY_BMAGIC_MAGIC013_03_H
#define OVERLAY_BMAGIC_MAGIC013_03_H

/* The bmagic/magic013/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern s32 D_1F800004;

extern Magic010Steps D_801EEC04;

extern Callback     D_801F03C0[];
extern u8           D_801F03D4[];
extern Callback     D_801F03DC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F03E4[];
#define BMAGIC_EFFECT_SLOTS D_801F03E4
#define BMAGIC_EFFECT_COUNT 64
/* func_800AED5C */
u8   Battle_CanTarget(s32 selector, u32 battler_index);
void func_801EF79C(void);
void func_801EF648(void);
void func_801EFAA8(void);
void func_801EFDB4(void);
void func_801F0164(void);

/* The wave band scratch: the wave height, the facing angle and the band shade, then the quad corners (g_ScratchPadVectors). */
#define WAVE_HEIGHT g_ScratchPad.cells.words[0]
#define WAVE_ANGLE  g_ScratchPad.cells.words[1]
#define WAVE_SHADE  g_ScratchPad.cells.words[2]

/* Draws the wave band of 16 shaded quads around the effect cell, turned by the facing table; LIFT is added to the
 * band height for the first and second corners. The caller declares prim, depth, flag, i and tpage. */
#define MAGIC013_DRAW_WAVE_BAND(lift)                                                                                                                                                             \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);                                                                                                                                  \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                                       \
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));                                                                                         \
    WAVE_SHADE                = SELF(PartyMember)->unk_04 * 12;                                                                                                                                   \
    WAVE_HEIGHT               = FIXED_MUL(rsin(0), 64);                                                                                                                                           \
    WAVE_ANGLE                = D_801F03D4[SELF(PartyMember)->facing] << 7;                                                                                                                       \
    g_ScratchPadVectors[3].vx = (u32)rsin(WAVE_ANGLE) >> 5;                                                                                                                                       \
    g_ScratchPadVectors[3].vy = (u32)rcos(WAVE_ANGLE) >> 5;                                                                                                                                       \
    g_ScratchPadVectors[3].vz = FIXED_MUL(rsin(0), WAVE_HEIGHT);                                                                                                                                  \
    for (i = 1; i <= 16; i++) {                                                                                                                                                                   \
        prim = (POLY_G4*)g_GfxPrimCursor;                                                                                                                                                         \
        SetPolyG4(prim);                                                                                                                                                                          \
        SetSemiTrans(prim, 1);                                                                                                                                                                    \
        WAVE_HEIGHT               = FIXED_MUL(rsin(i << 7), 64);                                                                                                                                  \
        WAVE_ANGLE                = ((D_801F03D4[SELF(PartyMember)->facing] + i) & 0x1F) << 7;                                                                                                    \
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[3].vx;                                                                                                                                    \
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[3].vy;                                                                                                                                    \
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[3].vz + (lift);                                                                                                                           \
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;                                                                                                                                    \
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;                                                                                                                                    \
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz;                                                                                                                                    \
        g_ScratchPadVectors[3].vx = (u32)rsin(WAVE_ANGLE) >> 5;                                                                                                                                   \
        g_ScratchPadVectors[3].vy = (u32)rcos(WAVE_ANGLE) >> 5;                                                                                                                                   \
        g_ScratchPadVectors[3].vz = FIXED_MUL(rsin((i & 3) << 10), WAVE_HEIGHT);                                                                                                                  \
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx;                                                                                                                                    \
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy;                                                                                                                                    \
        g_ScratchPadVectors[1].vz = g_ScratchPadVectors[3].vz + (lift);                                                                                                                           \
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, \
                      &depth, &flag);                                                                                                                                                             \
        setRGB0(prim, 1, 1, 1);                                                                                                                                                                   \
        setRGB1(prim, 1, 1, 1);                                                                                                                                                                   \
        setRGB2(prim, WAVE_SHADE, WAVE_SHADE, WAVE_SHADE);                                                                                                                                        \
        setRGB3(prim, WAVE_SHADE, WAVE_SHADE, WAVE_SHADE);                                                                                                                                        \
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));                                                                                     \
    }

#endif
