#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlots.h"

/* Mode entry: clears the effect slots, moves the task to the scroll target, spawns effect 0x61 and brightens the palette rows. */
MATCH void func_801EED18(void) {
    u16* dst;
    u16* src;
    u32  slot;
    s32  i;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    TASK(PartyMember)->pos.x.fixed  = g_AreaScrollTargetCoordX.fixed;
    TASK(PartyMember)->pos.y.fixed  = g_AreaScrollTargetCoordY.fixed;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0x38;
    TASK(PartyMember)->header.mode += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    slot                               = Battle_AllocEffect(1, 97) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    TASK(PartyMember)->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    i   = 0;
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
}

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F06E0, TASK(PartyMember)->header.step);
    if ((TASK(PartyMember)->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        Effect_SetActiveActorMatrix();
        func_801EF9F0();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF078(void) {
    TASK(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed + TO_COORD(0x160);
    TASK(PartyMember)->unk_25       = 0x1D;
    TASK(PartyMember)->unk_26       = 0;
    TASK(PartyMember)->unk_27       = 0x1A;
    TASK(PartyMember)->unk_28       = 1;
    TASK(PartyMember)->scale.x      = 0x10000;
    TASK(PartyMember)->scale.y      = 0x10000;
    TASK(PartyMember)->unk_48       = 0;
    TASK(PartyMember)->unk_5D       = 0;
    TASK(PartyMember)->unk_5E       = 0;
    TASK(PartyMember)->unk_5F       = 0;
    TASK(PartyMember)->unk_5C       = 0;
    TASK(PartyMember)->unk_2A       = 0;
    TASK(PartyMember)->unk_29       = 4;
    TASK(PartyMember)->unk_2C.value = 0;
    TASK(PartyMember)->unk_2B       = 0;
    TASK(PartyMember)->unk_24       = 0;
    Script_Select(0U);
    TASK(PartyMember)->unk_5D       = 0x10;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 10;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF1F4(void) {
    u8 count;

    Script_AnimStepOnce();
    TASK(PartyMember)->param.unk_0B += 0xC;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        TASK(PartyMember)->unk_09 = 0x1E;
        TASK(PartyMember)->timer  = 3;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF294(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           i;
    u8           slot;

    if (--TASK(PartyMember)->unk_09 == 0) {
        if (--TASK(PartyMember)->timer != 0) {
            for (i = 0; i < 16; i++) {
                slot = BMagic_AllocEffect();
                if (slot != GAME_NONE) {
                    battler                                = g_BattleEffectBattler;
                    BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                    BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                    BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
                    g_BattleEffectBattler->param.unk_0B += 1;
                }
            }
            if (TASK(PartyMember)->timer == 2) {
                SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 1));
            }
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 2));
            work         = TASK(PartyMember);
            work->unk_09 = 4;
            work->unk_0C = 0x800;
            TASK(PartyMember)->header.step += 1;
        } else {
            g_AreaCameraRefreshCount       = 93;
            TASK(PartyMember)->unk_09      = 60;
            TASK(PartyMember)->header.step = 4;
        }
    }
}

MATCH void func_801EF40C(void) {
    if (g_FrameCount & 0x1) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed - TASK(PartyMember)->unk_0C;
    } else {
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed - TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + TASK(PartyMember)->unk_0C;
    }
    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step--;
    }
}

/* Sways and spawns (MAGIC220_SWAY_AND_SPAWN), shakes the area camera with the
 * ticker's low bit and steps the handler at zero. */
MATCH void func_801EF4EC(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;
    u8           timer;

    MAGIC220_SWAY_AND_SPAWN();
    if (TASK(PartyMember)->unk_09 & 0x1) {
        g_AreaCameraOffsetX = 16;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->unk_09 = 32;
        TASK(PartyMember)->header.step += 1;
    }
}

/* Sways and spawns (MAGIC220_SWAY_AND_SPAWN), shakes the area camera by half
 * the ticker on odd ticks and steps the handler at zero. */
MATCH void func_801EF6B8(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;
    u8           timer;

    MAGIC220_SWAY_AND_SPAWN();
    if (TASK(PartyMember)->unk_09 & 0x1) {
        g_AreaCameraOffsetX = TASK(PartyMember)->unk_09 >> 1;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        g_AreaCameraOffsetX       = 0;
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderThree.h"

MATCH void func_801EF8CC(void) {
    s8 count;

    count = TASK(PartyMember)->unk_5D;
    if (count != 0) {
        TASK(PartyMember)->unk_5D = count - 2;
    }
    if (Script_AnimStepOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF9F0(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[5] = LOB(TASK(PartyMember)->unk_5D) * 4;
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

/* func_801EFC40 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->param.unk_0B * 2;
    g_ScratchPad.cells.halves[5] = (s8)TASK(PartyMember)->unk_5D * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(BMAGIC_LAYER_BEHIND_BATTLERS, 5);
}

MATCH void func_801EFF60(void) {
    SYS_DISPATCH_TASK(D_801F0700, 1, g_Task);
}

MATCH void func_801EFFA4(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F0704, func_801F0334);
}

MATCH void func_801F002C(void) {
    s16* angle_cell;
    u8   phase;

    angle_cell                     = &D_1F800004;
    phase                          = TASK(PartyMember)->param.unk_0B;
    *angle_cell                    = phase << 8;
    TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s8)phase << 8) * 24;
    TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * 24;
    TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    TASK(PartyMember)->unk_09      = 8;
    TASK(PartyMember)->timer       = 16;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801F010C(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = TASK(PartyMember)->param.unk_0B;
    *angle_cell = phase << 8;
    TASK(PartyMember)->pos.x.fixed += rsin((s16)(phase << 8)) * 3;
    TASK(PartyMember)->pos.y.fixed += rcos(*angle_cell) * 3;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F01C8(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = TASK(PartyMember)->param.unk_0B;
    *angle_cell = phase << 8;
    TASK(PartyMember)->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    TASK(PartyMember)->pos.y.fixed += rcos(*angle_cell) * 2;
    count                    = TASK(PartyMember)->timer - 2;
    TASK(PartyMember)->timer = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* Draw the magic220 glow as a textured diamond around the effect, its shade set by the timer. */
MATCH void func_801F0334(void) {
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
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->timer * 6;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rcos(ANGLE_45), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(ANGLE_45), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), 0);
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0628 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F068C */
#include "overlays/bmagic/shared/Actor_Clear.h"
