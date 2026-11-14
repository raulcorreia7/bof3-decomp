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
#define MAGIC121_DRAW_BOLT(COUNT, TURN)                                                                                                                        \
    run = 0;                                                                                                                                                   \
    if (GetGraphType() == 1) {                                                                                                                                 \
        tpage = 0xA5;                                                                                                                                          \
    } else if (GetGraphType() == 2) {                                                                                                                          \
        tpage = 0xA5;                                                                                                                                          \
    } else {                                                                                                                                                   \
        tpage = 0x35;                                                                                                                                          \
    }                                                                                                                                                          \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                    \
    GFX_AddPrim(3, sizeof(DR_MODE));                                                                                                                           \
    D_1F800000.view.effect.params[4] = g_Task->unk_2E.half;                                                                                                    \
    D_1F800000.view.effect.params[5] = g_Task->unk_30.half;                                                                                                    \
    for (i = 0; i < (COUNT) + 1; i++) {                                                                                                                        \
        D_1F800000.view.effect.params[4] += FIXED_MUL(rsin(g_Task->unk_14), 12);                                                                               \
        D_1F800000.view.effect.params[5] += FIXED_MUL(rcos(g_Task->unk_14), 12);                                                                               \
    }                                                                                                                                                          \
    D_1F800014[1].vx                 = D_1F800000.view.effect.params[4];                                                                                       \
    D_1F800014[1].vy                 = D_1F800000.view.effect.params[5];                                                                                       \
    D_1F800000.view.effect.params[2] = (g_Task->unk_14 + (TURN)) & 0xFFF;                                                                                      \
    D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), 32);                               \
    D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), 32);                               \
    D_1F800000.view.effect.params[0] = (u32)rsin(0) >> 8;                                                                                                      \
    D_1F800014[0].vx                 = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
    D_1F800014[0].vy                 = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]); \
    D_1F800000.view.effect.params[3] = ((rand() & 7) + 5) * g_Task->unk_04;                                                                                    \
    for (i = 1; i < 48; i++) {                                                                                                                                 \
        line = (LINE_F2*)g_GfxPrimCursor;                                                                                                                      \
        SetLineF2(line);                                                                                                                                       \
        SetSemiTrans(line, 1);                                                                                                                                 \
        D_1F800000.view.effect.params[0] = rand() & 7;                                                                                                         \
        run += D_1F800000.view.effect.params[0];                                                                                                               \
        if (run < 12) {                                                                                                                                        \
            D_1F800000.view.effect.params[4] += FIXED_MUL(rsin(g_Task->unk_14), D_1F800000.view.effect.params[0]);                                             \
            D_1F800000.view.effect.params[5] += FIXED_MUL(rcos(g_Task->unk_14), D_1F800000.view.effect.params[0]);                                             \
            D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), 32);                       \
            D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), 32);                       \
        } else {                                                                                                                                               \
            run                              = 0;                                                                                                              \
            D_1F800000.view.effect.params[4] = D_1F800014[1].vx + FIXED_MUL(rsin(g_Task->unk_14), 12);                                                         \
            D_1F800000.view.effect.params[5] = D_1F800014[1].vy + FIXED_MUL(rcos(g_Task->unk_14), 12);                                                         \
            D_1F800014[1].vx                 = D_1F800000.view.effect.params[4];                                                                               \
            D_1F800014[1].vy                 = D_1F800000.view.effect.params[5];                                                                               \
            D_1F800000.view.effect.params[6] = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), 32);                       \
            D_1F800000.view.effect.params[7] = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), 32);                       \
        }                                                                                                                                                      \
        D_1F800000.view.effect.params[1] = (i & 0x1F) << 6;                                                                                                    \
        wave                             = rsin(D_1F800000.view.effect.params[1]);                                                                             \
        D_1F800000.view.effect.params[0] = FIXED_MUL(wave, (rand() & 3) + 0x10);                                                                               \
        setXY0(line, D_1F800014[0].vx, D_1F800014[0].vy);                                                                                                      \
        D_1F800014[0].vx = D_1F800000.view.effect.params[6] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);             \
        line->x1         = D_1F800014[0].vx;                                                                                                                   \
        D_1F800014[0].vy = D_1F800000.view.effect.params[7] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);             \
        line->y1         = D_1F800014[0].vy;                                                                                                                   \
        setRGB0(line, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3] / 3);                               \
        GFX_AddPrim(3, sizeof(LINE_F2));                                                                                                                       \
    }                                                                                                                                                          \
    if (GetGraphType() == 1) {                                                                                                                                 \
        tpage = 0x25;                                                                                                                                          \
    } else if (GetGraphType() == 2) {                                                                                                                          \
        tpage = 0x25;                                                                                                                                          \
    } else {                                                                                                                                                   \
        tpage = 0x15;                                                                                                                                          \
    }                                                                                                                                                          \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                    \
    GFX_AddPrim(3, sizeof(DR_MODE));

#endif
