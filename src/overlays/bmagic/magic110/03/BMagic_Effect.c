#include "magic110_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* work;
    u32          slot;
    s32          i;
    u16*         src;
    u16*         dst;

    Battle_CenterCamera();
    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0x58;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 16) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    SELF(PartyMember)->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 16) & BYTE_MASK;
    work                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0x28;
    g_BattleEffects[slot].target.party = work;
    SELF(PartyMember)->param.unk_0B += 1;
    SELF(PartyMember)->param.unk_0B += 1;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores the color 0 of each. */
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 0; i < AREA_PALETTE_COLORS; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    for (i = 0; i < 16; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    g_GfxPalettePending                                          = 1;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE68(void) {
    if (SELF(PartyMember)->param.unk_0B == 2) {
        SND_SEQueueSelection(0x101);
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->timer  = 0;
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    u8 timer;
    u8 count;

    func_801EF148();
    if (g_FrameCount & 0x1) {
        timer = SELF(PartyMember)->timer;
        if (timer < 16U) {
            SELF(PartyMember)->timer = timer + 2;
        }
        count                     = SELF(PartyMember)->unk_09 + 1;
        SELF(PartyMember)->unk_09 = count;
        if ((count & BYTE_MASK) == 0x10) {
            SELF(PartyMember)->header.mode += 1;
        }
    }
}

MATCH void func_801EEF80(void) {
    u8           i;
    u32          slot;
    PartyMember* work;

    func_801EF148();
    if (SELF(PartyMember)->param.unk_0B == 0) {
        func_800A9610(g_Battle.target_selector, 16);
        for (i = 0; i < 6; i++) {
            slot                               = Battle_AllocEffect(1, 16) & BYTE_MASK;
            work                               = SELF(PartyMember);
            g_BattleEffects[slot].header.mode  = 2;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].target.party = work;
            SELF(PartyMember)->param.unk_0B += 1;
        }
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF068(void) {
    u8 timer;
    u8 count;

    func_801EF148();
    if (!(g_FrameCount & 0x3)) {
        timer = SELF(PartyMember)->timer;
        if (timer != 0) {
            SELF(PartyMember)->timer = timer - 1;
        }
        count                     = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = count;
        if (!(count & BYTE_MASK)) {
            Battle_MarkDamaged(g_Battle.target_selector);
            SELF(PartyMember)->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

/* Covers the screen with two semi-transparent quads in one flat shade of timer times 15;
 * the shade from byte 0x09 is stored first and overwritten. */
MATCH void func_801EF148(void) {
    POLY_G4* prim;
    s16*     shade;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    shade  = &D_1F800004;
    prim   = GFX_CURSOR(POLY_G4);
    *shade = SELF(PartyMember)->unk_09 * 15;
    *shade = SELF(PartyMember)->timer * 15;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, 319, 120);
    GFX_SET_RGB_ALL(prim, *shade, *shade, *shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    prim = GFX_CURSOR(POLY_G4);
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0x78, 319, 239);
    GFX_SET_RGB_ALL(prim, *shade, *shade, *shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

/* func_801EF3F8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF43C(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0478, SELF(PartyMember)->header.step);
    if ((SELF(PartyMember)->header.flags & 0x1) && SELF(PartyMember)->header.step >= 2) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

#include "overlays/bmagic/shared/Effect_CountDownTimerStep.h"

MATCH void func_801EF528(void) {
    PartyMember* work;
    PartyMember* next;

    work                      = SELF(PartyMember);
    work->screen_x.value      = 0xA0;
    work->unk_25              = 0x1D;
    next                      = SELF(PartyMember);
    work->screen_y.value      = 0x12C;
    next->unk_26              = 0;
    SELF(PartyMember)->unk_27 = 0x1A;
    SELF(PartyMember)->unk_28 = 1;
    SELF(PartyMember)->unk_24 = 0x80;
    {
        PartyMember* task;

        task          = SELF(PartyMember);
        task->unk_48  = 2;
        task->scale.x = 0x30000;
        task->scale.y = 0xC000;
    }
    SELF(PartyMember)->unk_5D       = 0;
    SELF(PartyMember)->unk_5E       = 0;
    SELF(PartyMember)->unk_5F       = 0;
    SELF(PartyMember)->unk_5C       = 0;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 2;
    SELF(PartyMember)->unk_2C.value = 0;
    SELF(PartyMember)->unk_2B       = 1;
    Script_Select(0);
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF648(void) {
    PartyMember* work;

    SELF(PartyMember)->screen_x.value = (RANDOM_MASK(3)) + 0x9F;
    work                              = SELF(PartyMember);
    work->screen_y.value -= 2;
    work->scale.y += 0x2000;
    if (work->scale.y > 0x17FFF) {
        work->header.step++;
    }
}

MATCH void func_801EF6B4(void) {
    u16 position;

    SELF(PartyMember)->screen_x.value = RANDOM_MASK(3) + 0x9F;
    position                          = SELF(PartyMember)->screen_y.value - 4;
    SELF(PartyMember)->screen_y.value = position;
    if ((s16)position < 178) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF740(void) {
    u16 position;

    SELF(PartyMember)->screen_x.value = RANDOM_MASK(3) + 0x9F;
    position                          = SELF(PartyMember)->screen_y.value - 2;
    SELF(PartyMember)->screen_y.value = position;
    if ((s16)position < 128) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF7B4(void) {
    SYS_DISPATCH_BYTE(D_801F048C, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFA48();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
}

MATCH void func_801EF844(void) {
    PartyMember* work;

    work              = SELF(PartyMember);
    work->unk_0C      = 0x60000;
    work->unk_10      = 0x60000;
    work->pos.x.fixed = g_AreaScrollTargetCoordX.fixed + work->unk_0C;
    work->pos.y.fixed = g_AreaScrollTargetCoordY.fixed + work->unk_10;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    work->unk_09      = 0x10;
    work->unk_14      = 0x100;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EF8C0(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if ((work->unk_14 += 0x40) == 0xC00) {
        work->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EFA48(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->unk_09 << 2;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 64; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 6, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]));
        setRGB1(prim, LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]));
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]));
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/shared/BMagic_DarkRingQuads.h"

/* func_801EFC98 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_14 + 0x80;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->unk_09 * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(BMAGIC_LAYER_FOREGROUND, 2);
}

MATCH void func_801EFFB8(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(D_801F049C, func_801F0138, func_801F01E8);
}

MATCH void func_801F0040(void) {
    PartyMember* work;
    s32*         channel;

    work                     = SELF(PartyMember);
    channel                  = &g_AreaScrollTargetX;
    work->pos.x.fixed        = channel[0] + D_801F04A4[work->param.unk_0B].x;
    work->pos.y.fixed        = channel[1] + D_801F04A4[work->param.unk_0B].y;
    work->pos.z.fixed        = g_BattleEffectBattler->pos.z.fixed;
    work->unk_09             = 0x60;
    SELF(PartyMember)->timer = 0x40;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801F00D8(void) {
    PartyMember* work;

    work         = SELF(PartyMember);
    work->unk_09 = work->unk_09 + 2;
    work         = SELF(PartyMember);
    work->timer  = work->timer - 1;
    if (work->timer == 0) {
        Effect_Reset();
    }
}

MATCH void Effect_SetActorMatrix2(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

MATCH void func_801F01E8(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 3;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->timer * 2;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rcos(ANGLE_45), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(ANGLE_45), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), 0);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the plain setClut sinks it below them. */
    *FAKE_VOLATILE_PTR(u16, &prim->clut) = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]), LOHU(g_ScratchPad.cells.halves[2]));
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
}
