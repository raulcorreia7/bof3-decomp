#include "magic103_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* func_801EEC70 */
MATCH void BMagic_SimoonInit(void) {
    u32  slot;
    u32  i;
    u16* dst;
    u16* src;

    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_SIMOON) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_SIMOON_EFFECT_SHADOW;
    SELF(PartyMember)->param.unk_0B    = 1;
    for (i = 0; i < 2; i++) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_SIMOON) & BYTE_MASK;
        g_BattleEffects[slot].target.party = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = BMAGIC_SIMOON_EFFECT_GLOW;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_SIMOON) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = BMAGIC_SIMOON_EFFECT_DOME;
    SELF(PartyMember)->param.unk_0B += 1;
    /* Copies the first two colour rows of arena palette 26 into the work copy with STP set, then clears colour 0 of each. */
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i]      = src[i] | PSX_COLOR_STP_BIT;
        dst[i + 16] = src[i + 16] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]  = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[16] = 0;
    g_GfxPalettePending                                           = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_Hit.h"

#include "shared/Effect_StartPlaying.h"

/* func_801EEEC8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEF0C */
MATCH void BMagic_SimoonDomeUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicSimoonDomeSteps, BMagic_SimoonDrawDome);
}

/* func_801EEF94 */
MATCH void BMagic_SimoonDomePlace(void) {
    PartyMember* src;

    src                                 = g_Battle.selected_actor;
    SELF(PartyMember)->pos.x.fixed      = src->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(src->pos.z);
    SELF(PartyMember)->unk_09           = 0;
    SELF(PartyMember)->timer            = 0;
    SELF(PartyMember)->header.step      = SELF(PartyMember)->header.step + 1;
}

/* func_801EEFF4 */
MATCH void BMagic_SimoonDomeGrow(void) {
    u8 counter;

    if (SELF(PartyMember)->unk_09 == 4) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
    }
    SP_REF(s16, 0)            = SELF(PartyMember)->unk_09 * 0x1C;
    counter                   = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x8) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EF094 */
MATCH void BMagic_SimoonDomeEnd(void) {
    u8 count;

    SP_REF(s16, 0u) = (SELF(PartyMember)->unk_09 * 4) + 0xC0;
    SELF(PartyMember)->timer += 1;
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* Draws an eight-band textured dome: band 24 down to 17 is a ring of 32 semi-transparent GT4 quads between the
 * radii and heights that rcos and rsin of the band give for the scratch radius word 0, each quad placed in its area
 * cell; v scrolls with timer and the shades fade in by row as unk_09 grows. */
/* func_801EF1D8 */
MATCH void BMagic_SimoonDrawDome(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       tpage;
    s32       band;
    s32       row;
    s32       i;
    s32       x;
    s32       y;

    for (band = 24, row = 1; band >= 17; band--, row++) {
        g_ScratchPad.cells.halves[3] = 0x81;
        g_ScratchPad.cells.halves[4] = 0x81;
        if (row - 1 < SELF(PartyMember)->unk_09 - 16) {
            g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 - 15 - row;
            if (g_ScratchPad.cells.halves[3] < 17) {
                g_ScratchPad.cells.halves[3] = 0x81 - g_ScratchPad.cells.halves[3] * 8;
            } else {
                g_ScratchPad.cells.halves[3] = 1;
            }
        }
        if (row < SELF(PartyMember)->unk_09 - 16) {
            g_ScratchPad.cells.halves[4] = SELF(PartyMember)->unk_09 - 16 - row;
            if (g_ScratchPad.cells.halves[4] < 17) {
                g_ScratchPad.cells.halves[4] = 0x81 - g_ScratchPad.cells.halves[4] * 8;
            } else {
                g_ScratchPad.cells.halves[4] = 1;
            }
        }
        g_ScratchPad.cells.halves[1] = FIXED_MUL(rcos((band - 1) << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPad.cells.halves[2] = FIXED_MUL(rcos(band << 7), g_ScratchPad.cells.halves[0]);
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]),
                  g_ScratchPadVectors[0].vz = FIXED_MUL(rsin((band - 1) << 7), g_ScratchPad.cells.halves[0]));
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]),
                  g_ScratchPadVectors[2].vz = FIXED_MUL(rsin(band << 7), g_ScratchPad.cells.halves[0]));
        for (i = 1; i <= 32; i++) {
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
            g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[1]);
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;
            g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[2]);
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[2]);
            x                         = (g_ScratchPadVectors[3].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                         = (g_ScratchPadVectors[3].vy << 9) + SELF(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
            prim = (POLY_GT4*)g_GfxPrimCursor;
            SetPolyGT4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x340, 0x100);
            prim->clut  = GetClut(0, 0x1FA);
            setUV4(prim, i * 8, (band - 16) * 8 + 32 + SELF(PartyMember)->timer * 4, i * 8 + 8, (band - 16) * 8 + 32 + SELF(PartyMember)->timer * 4, i * 8,
                   SELF(PartyMember)->timer * 4 + (band - 16) * 8 + 0x28, i * 8 + 8, SELF(PartyMember)->timer * 4 + (band - 16) * 8 + 0x28);
            setRGB0(prim, LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]));
            setRGB1(prim, LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]), LOHU(g_ScratchPad.cells.halves[4]));
            setRGB2(prim, LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]));
            setRGB3(prim, LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]), LOHU(g_ScratchPad.cells.halves[3]));
            Area_CellAddPrim(x, y, 2, sizeof(POLY_GT4));
        }
    }
}

/* func_801EF7CC */
/* Retail writes both radii to params[0], so the inner edge uses whatever params[1] holds. */
MATCH void BMagic_SimoonDrawRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      scale;

    scale                        = rcos(0x800) * 6;
    g_ScratchPad.cells.halves[0] = FIXED_MUL(scale, SELF(PartyMember)->unk_09 + 0xE1);
    scale                        = rcos(0x800) * 6;
    g_ScratchPad.cells.halves[0] = FIXED_MUL(scale, SELF(PartyMember)->unk_09 + 0xE0);
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);

    for (i = 1; i <= 32; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = 0;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]), 0);
        setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[1]), 0);
        g_ScratchPad.cells.halves[3] = 0x29 - SELF(PartyMember)->unk_09;
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
}

/* func_801EFB10 */
MATCH void BMagic_SimoonGlowUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicSimoonGlowSteps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        BMagic_SimoonDrawGlow();
    }
}

/* func_801EFB88 */
MATCH void BMagic_SimoonGlowPlace(void) {
    PartyMember* work;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        work                     = SELF(PartyMember);
        work->pos.x.fixed        = g_BattleSelectedActor->pos.x.fixed + g_BMagicSimoonGlowOffsets[work->param.unk_0B].x;
        work->pos.y.fixed        = g_BattleSelectedActor->pos.y.fixed + g_BMagicSimoonGlowOffsets[work->param.unk_0B].y;
        work->pos.z.fixed        = g_BattleSelectedActor->pos.z.fixed + g_BMagicSimoonGlowOffsets[work->param.unk_0B].z;
        work->unk_09             = 0;
        SELF(PartyMember)->timer = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFC70 */
MATCH void BMagic_SimoonGlowGrow(void) {
    u8 count;

    Battle_ProjectRange();
    SELF(PartyMember)->timer += 2;
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 8) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFCF4 */
MATCH void BMagic_SimoonGlowRise(void) {
    PartyMember* work;
    u8           counter;
    s32          drop;

    Battle_ProjectRange();
    work         = SELF(PartyMember);
    counter      = work->unk_09 + 1;
    drop         = (FAKE_VOLATILE(u8, work->unk_09) - 8) / 2;
    work->unk_09 = counter;
    work->screen_y.value -= drop;
    if ((counter & BYTE_MASK) == 0x1C) {
        SELF(PartyMember)->header.step += 1;
    }
}

/* func_801EFD74 */
MATCH void BMagic_SimoonGlowEnd(void) {
    u8 counter;

    Battle_ProjectRange();
    SELF(PartyMember)->screen_y.value -= (SELF(PartyMember)->unk_09 - 8) / 2;
    if ((SELF(PartyMember)->unk_09 & BYTE_MASK) != 0x2C) {
        SELF(PartyMember)->unk_09 = SELF(PartyMember)->unk_09 + 1;
    }
    counter                  = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer = counter;
    if (!(counter & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* Draw the magic103 tinted glow quad, turning with the effect timer (byte 0x09) around the
 * effect screen point. */
/* func_801EFE20 */
MATCH void BMagic_SimoonDrawGlow(void) {
    POLY_GT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    if (SELF(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 2;
    } else {
        g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->unk_09 - 8) / 4 + 0x10;
    }
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer * 8;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 7;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->timer * 4;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[7] = SELF(PartyMember)->screen_y.value;
    setXY4(prim, g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin((u8)(SELF(PartyMember)->unk_09 + 0x80) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos((u8)(SELF(PartyMember)->unk_09 + 0x80) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin((u8)(SELF(PartyMember)->unk_09 + 0x40) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos((u8)(SELF(PartyMember)->unk_09 + 0x40) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin((u8)(SELF(PartyMember)->unk_09 + 0xC0) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos((u8)(SELF(PartyMember)->unk_09 + 0xC0) << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(SELF(PartyMember)->unk_09 << 4), g_ScratchPad.cells.halves[0]),
           g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(SELF(PartyMember)->unk_09 << 4), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(16, 506);
    setUVWH(prim, 1, 1, 30, 30);
    GFX_SET_RGB_ALL(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_GT4));
}

/* func_801F02BC */
MATCH void BMagic_SimoonShadowUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicSimoonShadowSteps, BMagic_SimoonDrawShadow);
}

/* func_801F0344 */
MATCH void BMagic_SimoonShadowPlace(void) {
    PartyMember* src;

    src                            = g_Battle.selected_actor;
    SELF(PartyMember)->pos.x.fixed = src->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = src->pos.y.fixed;
    SELF(PartyMember)->pos.z       = src->pos.z;
    SELF(PartyMember)->unk_09      = 0;
    SELF(PartyMember)->timer       = 0;
    SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
}

/* func_801F03A4 */
MATCH void BMagic_SimoonShadowGrow(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    work->timer += 2;
    work = SELF(PartyMember);
    work->unk_09++;
    if (work->unk_09 == 8) {
        work = SELF(PartyMember);
        work->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpAndStepAt30.h"

#include "overlays/bmagic/shared/Effect_CountDownTimerCapped.h"

/* func_801F04E0 */
MATCH void BMagic_SimoonDrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;
    s32      scale;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    if (SELF(PartyMember)->header.step >= 2) {
        g_ScratchPad.cells.halves[0] = FIXED_MUL(SELF(PartyMember)->unk_09 * 4 + 0x160, rcos(0x800));
    } else {
        scale                        = rcos(0x800) * 48;
        g_ScratchPad.cells.halves[0] = FIXED_MUL(scale, SELF(PartyMember)->unk_09);
    }
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer << 3;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->timer * 6;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 16; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 8, g_ScratchPad.cells.halves[0]);
        setRGB0(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}
