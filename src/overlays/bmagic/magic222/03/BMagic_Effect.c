#include "magic222_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

/* func_801EEC70 */
MATCH void BMagic_CombustionInit(void) {
    u32  slot;
    s32  i;
    u16* dst;
    u16* src;

    Battle_CenterCamera();
    Battle_ProjectRange();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 16;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_COMBUSTION) & BYTE_MASK;
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].arg.unk_09   = 16;
    TASK(PartyMember)->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_COMBUSTION) & BYTE_MASK;
    g_BattleEffects[slot].target.party = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 16;
    TASK(PartyMember)->param.unk_0B += 1;
    /* Copies arena palette rows 26 and 2 into the work copy with STP set, then restores the first color of each. */
    for (i = 0, dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors, src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    {
        u16* row_dst;
        u16* row_src;

        for (i = 0, row_dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors, row_src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors; i < 16; i++) {
            *row_dst++ = *row_src++ | PSX_COLOR_STP_BIT;
        }
    }
    g_GfxPalettePending                                          = 1;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
}

#include "overlays/bmagic/shared/Effect_CountDownTimerQueueEffect.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEEE0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEF24 */
MATCH void BMagic_CombustionActorUpdate(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicCombustionActorSteps, TASK(PartyMember)->header.step);
    if ((TASK(PartyMember)->header.flags & 0x1) && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* func_801EEFC8 */
MATCH void BMagic_CombustionActorPlace(void) {
    PartyMember* work;

    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->unk_14       = TO_COORD(0x780);
        TASK(PartyMember)->unk_20       = TO_COORD(96);
        TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed + TASK(PartyMember)->unk_14;
        TASK(PartyMember)->unk_25       = 0x1D;
        TASK(PartyMember)->unk_26       = 0;
        TASK(PartyMember)->unk_27       = 0x1A;
        TASK(PartyMember)->unk_28       = 1;
        work                            = TASK(PartyMember);
        work->unk_48                    = 2;
        work->scale.x                   = 0x10000;
        work->scale.y                   = 0x10000;
        TASK(PartyMember)->unk_5D       = 0;
        TASK(PartyMember)->unk_5E       = 0;
        TASK(PartyMember)->unk_5F       = 0;
        TASK(PartyMember)->unk_5C       = 0;
        TASK(PartyMember)->unk_2A       = 0;
        TASK(PartyMember)->unk_29       = 4;
        TASK(PartyMember)->unk_2C.value = 0;
        TASK(PartyMember)->unk_2B       = 1;
        TASK(PartyMember)->unk_24       = 0;
        Script_Select(0U);
        TASK(PartyMember)->unk_09 = 0x10;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF148 */
MATCH void BMagic_CombustionActorFall(void) {
    u32 slot;
    u8  i;

    TASK(PartyMember)->unk_14 -= TASK(PartyMember)->unk_20;
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TASK(PartyMember)->unk_14;
    if (--TASK(PartyMember)->unk_09 == 0) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 1));
        for (i = 0; i < 8; i++) {
            slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_COMBUSTION) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 2;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        g_AreaCameraAngle.vx += 20;
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801EF274 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(22);
}

/* func_801EF324 */
MATCH void BMagic_CombustionActorSpawnWave(void) {
    u8           count;
    u32          slot;
    PartyMember* work;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x02));
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_COMBUSTION) & BYTE_MASK;
        work                               = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 3;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffectBattler->param.unk_0B += 1;
        TASK(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        TASK(PartyMember)->unk_5C = 1;
        TASK(PartyMember)->unk_5D = 0x40;
        TASK(PartyMember)->unk_5E = 0x40;
        TASK(PartyMember)->unk_5F = 0x40;
        TASK(PartyMember)->unk_09 = 12;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StartTint.h"

/* func_801EF4F0 */
MATCH void BMagic_CombustionActorFade(void) {
    TASK(PartyMember)->unk_5D -= 0x10;
    TASK(PartyMember)->unk_5E -= 0x10;
    TASK(PartyMember)->unk_5F -= 0x10;
    TASK(PartyMember)->scale.x += 0x1800;
    if ((s8)TASK(PartyMember)->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* func_801EF5A4 */
MATCH void BMagic_CombustionShadowUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicCombustionShadowSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Effect_SetActorMatrix();
        BMagic_CombustionDrawShadow();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
}

/* func_801EF634 */
MATCH void BMagic_CombustionShadowPlace(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--TASK(PartyMember)->unk_09 == 0) {
        src                      = g_BattleEffectBattler;
        dst                      = TASK(PartyMember);
        dst->pos.x.fixed         = src->pos.x.fixed;
        dst->pos.y.fixed         = src->pos.y.fixed;
        dst->pos.z               = src->pos.z;
        dst->unk_14              = 0;
        dst->unk_09              = 0;
        TASK(PartyMember)->timer = 38;
        TASK(PartyMember)->header.step++;
    }
}

/* func_801EF6C8 */
MATCH void BMagic_CombustionShadowGrow(void) {
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->unk_14 += 6;
    if (TASK(PartyMember)->unk_09 == 0x10) {
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownAndStep.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801EF87C */
MATCH void BMagic_CombustionDrawShadow(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 << 2;
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]), 0);
    g_ScratchPadVectors[1].vz = 0;
    g_ScratchPadVectors[0].vz = 0;

    for (i = 1; i <= 64; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 6, g_ScratchPad.cells.halves[0]);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB1(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/shared/BMagic_DarkRingQuads.h"

/* func_801EFACC */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_14;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_14 * 2;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->unk_09 * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(BMAGIC_LAYER_BEHIND_BATTLERS, 5);
}

/* func_801EFDEC */
MATCH void BMagic_CombustionSparkUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW_IN_OWN_MATRIX(g_BMagicCombustionSparkSteps, Effect_SetActorMatrix3, BMagic_CombustionDrawSpark);
}

/* func_801EFE74 */
MATCH void BMagic_CombustionSparkPlace(void) {
    s32  r;
    s32  phase;
    s16* angle = &D_1F800004;

    r                              = rand();
    phase                          = TASK(PartyMember)->param.unk_0B;
    TASK(PartyMember)->unk_0C      = (r & 0x7) + 8;
    *angle                         = phase << 9;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * TASK(PartyMember)->unk_0C);
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * TASK(PartyMember)->unk_0C);
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    TASK(PartyMember)->unk_09      = 8;
    TASK(PartyMember)->timer       = 16;
    TASK(PartyMember)->header.step += 1;
}

/* func_801EFF7C */
MATCH void BMagic_CombustionSparkFly(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = TASK(PartyMember);
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 1;
    *angle_cell                    = direction << 9;
    velocity                       = rsin((s16)(direction << 9)) * TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity                       = rcos(*angle_cell) * TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

/* func_801F0070 */
MATCH void BMagic_CombustionSparkEnd(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = TASK(PartyMember)->param.unk_0B;
    TASK(PartyMember)->unk_0C += 1;
    *angle_cell                    = phase << 9;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 9)) * TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * TASK(PartyMember)->unk_0C;
    count                          = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer       = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void Effect_SetActorMatrix3(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    BMAGIC_SET_ACTOR_MATRIX();
}

/* func_801F0218 */
MATCH void BMagic_CombustionDrawSpark(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[0] = 0x100;
    D_1F80000A                   = TASK(PartyMember)->timer << 3;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rcos(ANGLE_45), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(ANGLE_45), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), 0);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the best pure-C body is 0x2C8 against retail's 0x2D4. */
    *FAKE_VOLATILE_PTR(u16, &prim->clut) = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, D_1F80000A, D_1F80000A, D_1F80000A);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0504 */
MATCH void BMagic_CombustionWaveUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicCombustionWaveSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        BMagic_CombustionDrawWave();
        BMagic_CombustionDrawWave();
    }
}

/* func_801F0584 */
MATCH void BMagic_CombustionWavePlace(void) {
    PartyMember* src;

    src                               = g_BattleEffectBattler;
    TASK(PartyMember)->screen_x.value = src->screen_x.value;
    TASK(PartyMember)->screen_y.value = src->screen_y.value;
    func_800A9610(g_Battle.target_selector, 16);
    TASK(PartyMember)->param.unk_0B = 8;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 4;
    TASK(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_CountUpByTwoAndStep.h"

/* func_801F066C */
MATCH void BMagic_CombustionWaveWait(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer - 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 0) {
        TASK(PartyMember)->timer       = 16;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

/* func_801F06C8 */
MATCH void BMagic_CombustionWaveRise(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->param.unk_0B += 4;
    work = TASK(PartyMember);
    work->timer--;
    if (work->timer == 0) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}

/* func_801F0730 */
MATCH void BMagic_CombustionWaveEnd(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = TASK(PartyMember);
    work->param.unk_0B += 4;
    work         = TASK(PartyMember);
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Effect_Reset();
    }
}

/* func_801F07A8 */
MATCH void BMagic_CombustionDrawWave(void) {
    POLY_G4*     prim;
    PartyMember* work;
    s32          tpage;
    s32          i;
    s16          x;
    s16          y;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    work                         = TASK(PartyMember);
    g_ScratchPad.cells.halves[0] = work->param.unk_0B;
    g_ScratchPad.cells.halves[1] = work->param.unk_0B * 2;
    g_ScratchPad.cells.halves[5] = work->unk_09 * 15;
    g_ScratchPad.cells.halves[6] = work->unk_09 * 8;
    g_ScratchPad.cells.halves[7] = work->unk_09 * 8;
    x                            = work->screen_x.value - 0x100;
    y                            = work->screen_y.value;
    for (i = 0; (u32)(i & BYTE_MASK) < 32; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[0]));
        prim->x2 = x;
        prim->y2 = y;
        prim->x1 = x + 16;
        prim->y1 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[0]);
        prim->x3 = x + 16;
        prim->y3 = y;
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB1(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB3(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[1]));
        prim->x2 = x;
        prim->y2 = y + FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[0]);
        prim->x1 = x + 16;
        prim->y1 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[1]);
        prim->x3 = x + 16;
        prim->y3 = y + FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB3(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[0]));
        prim->x2 = x;
        prim->y2 = y;
        prim->x1 = x + 16;
        prim->y1 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[0]);
        prim->x3 = x + 16;
        prim->y3 = y;
        setRGB0(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB1(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        setRGB3(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[5]));
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));

        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, x, y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[1]));
        prim->x2 = x;
        prim->y2 = y - FIXED_MUL(rsin((i & BYTE_MASK) << 6), g_ScratchPad.cells.halves[0]);
        prim->x1 = x + 16;
        prim->y1 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[1]);
        prim->x3 = x + 16;
        prim->y3 = y - FIXED_MUL(rsin(((i & BYTE_MASK) + 1) << 6), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        setRGB3(prim, LOHU(g_ScratchPad.cells.halves[5]), LOHU(g_ScratchPad.cells.halves[6]), LOHU(g_ScratchPad.cells.halves[7]));
        GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));

        x += 16;
    }
}
