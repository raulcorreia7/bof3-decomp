#include "magic121_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEE08};
    SYS_DISPATCH_TASK(handlers, 1, g_Self);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* battler;
    u32          slot;
    u32          i;
    u16*         dst;
    u16*         src;

    SELF(PartyMember)->facing          = g_BattleEffectBattler->facing;
    battler                            = g_BattleEffectBattler;
    task                               = SELF(PartyMember);
    task->pos.x.fixed                  = battler->pos.x.fixed;
    task->pos.y.fixed                  = battler->pos.y.fixed;
    task->pos.z.fixed                  = battler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 90) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 4;
    /* Copies the first three colour rows of arena palette 26 into the work copy, STP set on rows 0 and 2. */
    dst                                = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src                                = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i + 16] = src[i + 16];
    }
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i + 32] = src[i + 32] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]  = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[16] = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[32] = 0;
    g_GfxPalettePending                                           = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

/* func_801EEE68 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void BMagic_UpdateDragonBreath(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Self);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        if ((g_FrameCount & 0x7) == 0) {
            SELF(PartyMember)->unk_5D = RANDOM_MASK(1);
            SELF(PartyMember)->unk_5E = RANDOM_MASK(3);
            SELF(PartyMember)->unk_5F = RANDOM_MASK(3);
        }
        func_801F0198(SELF(PartyMember)->unk_5D + 3);
        func_801F0198(SELF(PartyMember)->unk_5E + 7);
        func_801F0198(11 - SELF(PartyMember)->unk_5F);
        func_801F06E8(4 - SELF(PartyMember)->unk_5D);
        func_801F06E8(SELF(PartyMember)->unk_5F + 8);
        func_801F06E8(12 - SELF(PartyMember)->unk_5E);
        BMagic_DrawDragonBreath();
    }
}

/* Aim the dragon breath: stage the target screen point, project the caster, step its screen
 * point once and face the shot from there to the target. */
MATCH void func_801EF03C(void) {
    PartyMember* task;
    PartyMember* battler;
    PartyMember* work;
    PartyMember* effect;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        D_1F800008[2] = SELF(PartyMember)->screen_x.value;
        D_1F800008[3] = SELF(PartyMember)->screen_y.value;
        func_800B0118();
        battler           = g_BattleEffectBattler;
        task              = SELF(PartyMember);
        task->pos.x.fixed = battler->pos.x.fixed;
        task->pos.y.fixed = battler->pos.y.fixed;
        task->pos.z.fixed = battler->pos.z.fixed;
        Battle_ProjectRange();
        SELF(PartyMember)->screen_x.value += SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->screen_y.value += SELF(PartyMember)->unk_10;
        D_1F800008[0]                   = SELF(PartyMember)->screen_x.value;
        D_1F800008[1]                   = SELF(PartyMember)->screen_y.value;
        SELF(PartyMember)->unk_14       = ratan2(D_1F800008[2] - D_1F800008[0], D_1F800008[3] - D_1F800008[1]);
        SELF(PartyMember)->unk_5D       = RANDOM_MASK(1);
        SELF(PartyMember)->unk_5E       = RANDOM_MASK(3);
        SELF(PartyMember)->unk_5F       = RANDOM_MASK(3);
        effect                          = SELF(PartyMember);
        effect->unk_04                  = 0;
        effect->unk_0C                  = 0;
        SELF(PartyMember)->param.unk_0B = 0;
        SELF(PartyMember)->unk_09       = 16;
        SELF(PartyMember)->timer        = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF218(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 8, 32);
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer                           = SELF(PartyMember)->param.unk_0B + 1;
    SELF(PartyMember)->param.unk_0B = timer;
    if (timer == 8) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF324(void) {
    PartyMember* work;

    work = SELF(PartyMember);
    if (++work->unk_0C == 0x2E) {
        work->header.step++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_04 - 2;
    SELF(PartyMember)->unk_04 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF3A8(void) {
    u8 ticks;
    u8 count;

    ticks = SELF(PartyMember)->param.unk_0B;
    if (ticks != 0) {
        SELF(PartyMember)->param.unk_0B = ticks - 1;
    }
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

/* Lays the dragon breath on the caster's screen point: two spine points step 12 units down the
 * heading unk_14, and every step rings them with four semi-transparent quads - a narrow lip and a
 * wider skirt at heading + 0x400, and the same pair at heading - 0x400 - shaded by unk_09 * 15,
 * its quarter on the trailing edges and white on the wide face. */
MATCH void BMagic_DrawDragonBreath(void) {
    POLY_G4* prim;
    s32      tpage;
    s16      i;
    s16      jitter;
    s16      prev_jitter;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    jitter                       = 0;
    g_ScratchPad.cells.halves[4] = SELF(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->screen_y.value;
    for (i = 1; i < SELF(PartyMember)->timer + 1; i++) {
        /* The old spine point becomes the near end of this step's ribbon. */
        g_ScratchPad.cells.halves[6] = g_ScratchPad.cells.halves[4];
        g_ScratchPad.cells.halves[7] = g_ScratchPad.cells.halves[5];
        g_ScratchPad.cells.halves[4] += FIXED_MUL(rsin(SELF(PartyMember)->unk_14), 12);
        g_ScratchPad.cells.halves[5] += FIXED_MUL(rcos(SELF(PartyMember)->unk_14), 12);
        /* The ribbon keeps its last thickness once the step index reaches four. */
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * 4;
        if (i - 1 < 4) {
            g_ScratchPad.cells.halves[0] = SELF(PartyMember)->param.unk_0B * (i - 1);
        }
        if (i < 4) {
            g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * i;
        }
        g_ScratchPad.cells.halves[3] = SELF(PartyMember)->unk_09 * 15;
        prev_jitter                  = jitter;
        jitter                       = rand() & 3;
        prim                         = (POLY_G4*)g_GfxPrimCursor;
        g_ScratchPad.cells.halves[0] += prev_jitter;
        g_ScratchPad.cells.halves[1] += jitter;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        /* Lit lip: the near side swings off both spine points at heading + 0x400. */
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_14 + 0x400) & ANGLE_MASK;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->x0                     = g_ScratchPad.cells.halves[6];
        prim->y0                     = g_ScratchPad.cells.halves[7];
        prim->x2                     = g_ScratchPad.cells.halves[4];
        prim->y2                     = g_ScratchPad.cells.halves[5];
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
        /* Far lip: the same pair of widths swung the other way, heading - 0x400. */
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_14 - 0x400) & ANGLE_MASK;
        prim->x0                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y0                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->x1                     = g_ScratchPad.cells.halves[6];
        prim->y1                     = g_ScratchPad.cells.halves[7];
        prim->x3                     = g_ScratchPad.cells.halves[4];
        prim->y3                     = g_ScratchPad.cells.halves[5];
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
        /* Skirt: a ring four units thicker than the rib, white on its wide face. */
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_14 + 0x400) & ANGLE_MASK;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B + 4) * 4;
        if (i - 1 < 4) {
            g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->param.unk_0B + 4) * (i - 1);
        }
        if (i < 4) {
            g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B + 4) * i;
        }
        g_ScratchPad.cells.halves[0] += prev_jitter;
        g_ScratchPad.cells.halves[1] += jitter;
        prim->x1                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * 4;
        if (i - 1 < 4) {
            g_ScratchPad.cells.halves[0] = SELF(PartyMember)->param.unk_0B * (i - 1);
        }
        if (i < 4) {
            g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * i;
        }
        g_ScratchPad.cells.halves[0] += prev_jitter;
        g_ScratchPad.cells.halves[1] += jitter;
        prim->x0 = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y0 = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x2 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB1(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
        /* Far skirt: the wide ring on the far side, heading - 0x400, mirrored across the rib. */
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        g_ScratchPad.cells.halves[2] = (SELF(PartyMember)->unk_14 - 0x400) & ANGLE_MASK;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B + 4) * 4;
        if (i - 1 < 4) {
            g_ScratchPad.cells.halves[0] = (SELF(PartyMember)->param.unk_0B + 4) * (i - 1);
        }
        if (i < 4) {
            g_ScratchPad.cells.halves[1] = (SELF(PartyMember)->param.unk_0B + 4) * i;
        }
        g_ScratchPad.cells.halves[0] += prev_jitter;
        g_ScratchPad.cells.halves[1] += jitter;
        prim->x0                     = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y0                     = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * 4;
        if (i - 1 < 4) {
            g_ScratchPad.cells.halves[0] = SELF(PartyMember)->param.unk_0B * (i - 1);
        }
        if (i < 4) {
            g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * i;
        }
        g_ScratchPad.cells.halves[0] += prev_jitter;
        g_ScratchPad.cells.halves[1] += jitter;
        prim->x1 = g_ScratchPad.cells.halves[6] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1 = g_ScratchPad.cells.halves[7] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3 = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3 = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB1(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3] / 4, g_ScratchPad.cells.halves[3] / 4);
        setRGB0(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
}

MATCH void func_801F0198(u8 count) {
    LINE_F2* line;
    s32      tpage;
    s32      i;
    s32      run;
    s32      wave;

    MAGIC121_DRAW_BOLT(count, 0x400);
}

MATCH void func_801F06E8(u8 count) {
    LINE_F2* line;
    s32      tpage;
    s32      i;
    s32      run;
    s32      wave;

    MAGIC121_DRAW_BOLT(count, -0x400);
}
