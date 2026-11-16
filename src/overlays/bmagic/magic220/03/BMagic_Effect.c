#include "magic220_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EED18(void) {
    u16* dst;
    u16* src;
    u32  slot;
    s32  i;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    g_Task->pos.x.fixed  = g_AreaScrollTargetX;
    g_Task->unk_09       = 0x38;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    g_Task->pos.y.fixed = g_AreaScrollTargetY;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    slot                               = Battle_AllocEffect(1, 0x61) & BYTE_MASK;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = g_Task;
    g_Task->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    for (; i < 16; i++) {
        *dst++ = *src++ | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                      = 1;
}
#else
INCLUDE_ASM(func_801EED18);
#endif

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEF78 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFBC(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F06E0, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
        Effect_SetActiveActorMatrix();
        func_801EF9F0();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF078(void) {
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(0x160);
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->unk_27      = 0x1A;
    g_Task->unk_28      = 1;
    g_Task->scale.x     = 0x10000;
    g_Task->scale.y     = 0x10000;
    g_Task->unk_48      = 0;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    g_Task->unk_24      = 0;
    Actor_SelectScript(0U);
    g_Task->unk_5D       = 0x10;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 10;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF1F4(void) {
    u8 count;

    Actor_StepAnimOnce();
    g_Task->param.unk_0B += 0xC;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 0x1E;
        g_Task->timer  = 3;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF294(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           i;
    u8           slot;

    if (--g_Task->unk_09 == 0) {
        if (--g_Task->timer != 0) {
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
            if (g_Task->timer == 2) {
                SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 1));
            }
            SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 2));
            work         = g_Task;
            work->unk_09 = 4;
            work->unk_0C = 0x800;
            g_Task->header.step += 1;
        } else {
            g_AreaCameraRefreshCount = 93;
            g_Task->unk_09           = 60;
            g_Task->header.step      = 4;
        }
    }
}

MATCH void func_801EF40C(void) {
    if (g_FrameCount & 0x1) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed - g_Task->unk_0C;
    } else {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed - g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_0C;
    }
    if (--g_Task->unk_09 == 0) {
        g_Task->unk_09 = 8;
        g_Task->header.step--;
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
    if (g_Task->unk_09 & 0x1) {
        g_AreaCameraOffsetX = 16;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = 32;
        g_Task->header.step += 1;
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
    if (g_Task->unk_09 & 0x1) {
        g_AreaCameraOffsetX = g_Task->unk_09 >> 1;
    } else {
        g_AreaCameraOffsetX = 0;
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_AreaCameraOffsetX = 0;
        g_Task->unk_09      = 8;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

MATCH void func_801EF8CC(void) {
    s8 count;

    count = g_Task->unk_5D;
    if (count != 0) {
        g_Task->unk_5D = count - 2;
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

MATCH void func_801EF9F0(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 2, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(5, tpage);
    D_1F800000.cells.halves[0] = g_Task->param.unk_0B;
    D_1F800000.cells.halves[5] = LOB(g_Task->unk_5D) * 4;
    setVector(&D_1F800014[2], FIXED_MUL(rsin(0), D_1F800000.cells.halves[0]), FIXED_MUL(rcos(0), D_1F800000.cells.halves[0]), 0);
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;

    for (i = 1; i <= 64; i++) {
        prim = GFX_BeginPolyG3(1);
        GFX_STEP_TRIANGLE_FAN(i << 6, D_1F800000.cells.halves[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]));
        setRGB1(prim, LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]));
        setRGB2(prim, LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]), LOHU(D_1F800000.cells.halves[5]));
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
}

#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFC40 */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(5, getTPage(0, 2, 320, 256));
    D_1F800000.cells.halves[0] = g_Task->param.unk_0B;
    D_1F800000.cells.halves[1] = g_Task->param.unk_0B * 2;
    D_1F800000.cells.halves[5] = (s8)g_Task->unk_5D * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
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

    angle_cell          = &D_1F800004;
    phase               = g_Task->param.unk_0B;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s8)phase << 8) * 24;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * 24;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 16;
    g_Task->header.step += 1;
}

MATCH void func_801F010C(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = g_Task->param.unk_0B;
    *angle_cell = phase << 8;
    g_Task->pos.x.fixed += rsin((s16)(phase << 8)) * 3;
    g_Task->pos.y.fixed += rcos(*angle_cell) * 3;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F01C8(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = g_Task->param.unk_0B;
    *angle_cell = phase << 8;
    g_Task->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    g_Task->pos.y.fixed += rcos(*angle_cell) * 2;
    count         = g_Task->timer - 2;
    g_Task->timer = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* Draw the magic220 glow as a textured diamond around the effect, its shade set by the timer. */
MATCH void func_801F0334(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.cells.halves[0] = 0x100;
    D_1F800000.cells.halves[5] = g_Task->timer * 6;
    setVector(&D_1F800014[0], FIXED_MUL(rcos(ANGLE_45), D_1F800000.cells.halves[0]), FIXED_MUL(rsin(ANGLE_45), D_1F800000.cells.halves[0]), 0);
    setVector(&D_1F800014[1], FIXED_MUL(rcos(1536), D_1F800000.cells.halves[0]), FIXED_MUL(rsin(1536), D_1F800000.cells.halves[0]), 0);
    setVector(&D_1F800014[2], FIXED_MUL(rcos(3584), D_1F800000.cells.halves[0]), FIXED_MUL(rsin(3584), D_1F800000.cells.halves[0]), 0);
    setVector(&D_1F800014[3], FIXED_MUL(rcos(2560), D_1F800000.cells.halves[0]), FIXED_MUL(rsin(2560), D_1F800000.cells.halves[0]), 0);
    prim->tpage = GetTPage(0, 1, 832, 256);
    prim->clut  = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, D_1F800000.cells.halves[5], D_1F800000.cells.halves[5], D_1F800000.cells.halves[5]);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F0628 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F068C */
#include "overlays/bmagic/Actor_Clear.h"
