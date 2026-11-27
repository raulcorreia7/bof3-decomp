#ifndef OVERLAY_BMAGIC_MAGIC121_03_H
#define OVERLAY_BMAGIC_MAGIC121_03_H

/* The bmagic/magic121/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

void func_801EEE08(void);
void func_801F0198(u8 count);
void func_801F06E8(u8 count);
void BMagic_DrawDragonBreath(void);

/* The two staged screen points: the target (+0x04) and the start (+0x00). */
extern s16 D_1F800008[];

/* Draws one flickering bolt of the dragon breath: a start point COUNT + 1 steps of 12 along the heading
 * unk_14, then 47 LINE_F2 segments that run on by random steps (back to a fresh start every 12) and swing
 * across the bolt by a sine, offset 32 to the side at heading + TURN. A statement macro: the member declares
 * line, tpage, i, run and wave. */
#define MAGIC121_DRAW_BOLT(COUNT, TURN)                                                                                                         \
    run   = 0;                                                                                                                                  \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);                                                                                \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                     \
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MODE));                                                                                   \
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;                                                                           \
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;                                                                           \
    for (i = 0; i < (COUNT) + 1; i++) {                                                                                                         \
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(SELF(PartyMember)->unk_14), 12);                                                         \
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(SELF(PartyMember)->unk_14), 12);                                                         \
    }                                                                                                                                           \
    g_ScratchPadVectors[1].vx    = g_ScratchPad.cells.halves[4];                                                                                \
    g_ScratchPadVectors[1].vy    = g_ScratchPad.cells.halves[5];                                                                                \
    g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_14 + (TURN)) & 0xFFF;                                                                \
    g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 32);                            \
    g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 32);                            \
    g_ScratchPad.cells.halves[0] = (u32)rsin(0) >> 8;                                                                                           \
    g_ScratchPadVectors[0].vx    = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);  \
    g_ScratchPadVectors[0].vy    = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);  \
    g_ScratchPad.cells.halves[3] = ((rand() & 7) + 5) * SELF(PartyMember)->unk_04;                                                              \
    for (i = 1; i < 48; i++) {                                                                                                                  \
        line = (LINE_F2*)g_GfxPrimCursor;                                                                                                       \
        SetLineF2(line);                                                                                                                        \
        SetSemiTrans(line, 1);                                                                                                                  \
        g_ScratchPad.cells.halves[0] = rand() & 7;                                                                                              \
        run += g_ScratchPad.cells.halves[0];                                                                                                    \
        if (run < 12) {                                                                                                                         \
            g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(SELF(PartyMember)->unk_14), g_ScratchPad.cells.halves[0]);                           \
            g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(SELF(PartyMember)->unk_14), g_ScratchPad.cells.halves[0]);                           \
            g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 32);                    \
            g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 32);                    \
        } else {                                                                                                                                \
            run                          = 0;                                                                                                   \
            g_ScratchPad.cells.halves[4] = g_ScratchPadVectors[1].vx + FIXED_MUL(rsin(SELF(PartyMember)->unk_14), 12);                          \
            g_ScratchPad.cells.halves[5] = g_ScratchPadVectors[1].vy + FIXED_MUL(rcos(SELF(PartyMember)->unk_14), 12);                          \
            g_ScratchPadVectors[1].vx    = g_ScratchPad.cells.halves[4];                                                                        \
            g_ScratchPadVectors[1].vy    = g_ScratchPad.cells.halves[5];                                                                        \
            g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), 32);                    \
            g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), 32);                    \
        }                                                                                                                                       \
        g_ScratchPad.cells.halves[1] = (i & 0x1F) << 6;                                                                                         \
        wave                         = rsin(g_ScratchPad.cells.halves[1]);                                                                      \
        g_ScratchPad.cells.halves[0] = FIXED_MUL(wave, (rand() & 3) + 0x10);                                                                    \
        setXY0(line, g_ScratchPadVectors[0].vx, g_ScratchPadVectors[0].vy);                                                                     \
        g_ScratchPadVectors[0].vx = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]); \
        line->x1                  = g_ScratchPadVectors[0].vx;                                                                                  \
        g_ScratchPadVectors[0].vy = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]); \
        line->y1                  = g_ScratchPadVectors[0].vy;                                                                                  \
        setRGB0(line, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 3);                            \
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(LINE_F2));                                                                               \
    }                                                                                                                                           \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);                                                                               \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                     \
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(DR_MODE));

#endif
