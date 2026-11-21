#include "magic223_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlots.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EED18(void) {
    BattleEffectTargetColumn* targets;
    PartyMember*              target;
    u32                       i;
    u32                       slot;
    u16*                      palette;
    u16*                      arena;

    i = 0;
    do {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
        i++;
    } while (i < BMAGIC_EFFECT_COUNT);

    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x        = g_BattleEffectBattler->pos.x;
    g_Task->pos.y        = g_BattleEffectBattler->pos.y;
    g_Task->pos.z        = g_BattleEffectBattler->pos.z;
    g_Task->unk_09       = 8;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode++;

    slot                               = Battle_AllocEffect(1, 0x63) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = target;
    g_Task->param.unk_0B++;

    for (i = 0; i < 0x30; i++) {
        slot = BMagic_AllocEffect() & BYTE_MASK;
        if (slot != BYTE_MASK) {
            target                                = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B      = i;
            targets                               = (BattleEffectTargetColumn*)&BMAGIC_EFFECT_SLOTS[13].unk_5C;
            targets[slot].target.party            = target;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09  = ((i >> 3) << 4) + (rand() & 0xF) + 1;
            g_Task->param.unk_0B++;
        }
    }

    arena   = BATTLE_PALETTE_SOURCE_COLORS;
    palette = BATTLE_EFFECT_PALETTE_COLORS;
    for (i = 1; i < 0x10; i++) {
        palette[0]  = arena[0] | 0x8000;
        palette[16] = arena[16] | 0x8000;
        palette++;
        arena++;
    }
    BATTLE_EFFECT_PALETTE_COLORS[-1] = 0;
    BATTLE_EFFECT_PALETTE_COLORS[15] = 0;
    g_GfxPalettePending              = 1;
    SND_QueueSelectionSE(0x100);
}
#else
INCLUDE_ASM(func_801EED18);
#endif

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

/* When the effect ticker is zero, marks the hit applied and the effect playing, tells the battle UI and
 * runs the effect player's follow-up. */
MATCH void func_801EEFB4(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_DAMAGE_APPLIED | BATTLE_STATE_EFFECT_PLAYING);
        func_800A9820(g_Battle.target_selector);
        Effect_Reset();
    }
}

/* func_801EF00C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF050(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 2, g_Task);
    if (g_Task->header.flags != 0) {
        func_801EF1E8();
    }
}

#include "overlays/bmagic/shared/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/shared/Effect_CountUpAndStep.h"

#include "overlays/bmagic/shared/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/shared/Effect_TickOnTimerZero.h"

MATCH void func_801EF1E8(void) {
    POLY_G4* prim;
    s32*     dark;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 0x13F, 0, 0, 0, 0x13F, 0xEF, 0, 0xEF);
    }
    dark       = &D_1F800008;
    *dark      = g_Task->unk_09;
    D_1F80000C = g_Task->unk_09 * 8;
    setRGB0(prim, prim->r3 = D_1F80000C, prim->g3 = D_1F80000C, prim->b3 = D_1F80000C);
    setRGB1(prim, prim->r2 = *dark, prim->g2 = *dark, prim->b2 = *dark);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_G4));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, tpage);
}

MATCH void func_801EF3C0(void) {
    SYS_DISPATCH_TASK(D_801EFC40, 1, g_Task);
}

MATCH void func_801EF404(void) {
    SYS_DISPATCH_BYTE(D_801EFC44, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF7A8();
    }
}

MATCH void func_801EF47C(void) {
    s32* angle_cell;
    s32  phase;

    if (--g_Task->unk_09 == 0) {
        g_Task->facing      = g_BattleEffectBattler->facing;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        Battle_ProjectRange();
        angle_cell  = &D_1F800004;
        phase       = (g_Task->param.unk_0B & 7) << 8;
        *angle_cell = phase;
        phase += ANGLE_90;
        *angle_cell = phase + D_801EFC50[g_Task->facing];
        g_Task->unk_2E.value += (rsin(*angle_cell) * 72) >> 0xC;
        g_Task->unk_30.value += (rcos(*angle_cell) * 72) >> 0xC;
        g_Task->unk_14 = D_801EFC50[g_Task->facing];
        if (LOHU(g_Battle.action_id) == ABILITY_TEMPEST) {
            g_Task->param.unk_0B = 0;
        } else {
            g_Task->param.unk_0B = 0x10;
        }
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF628(void) {
    s32 offset;
    u8  timer;

    g_Task->unk_2E.value += (rsin(g_Task->unk_14) * 8) >> 0xC;
    offset = (rcos(g_Task->unk_14) * 8) >> 0xC;
    g_Task->unk_30.value += offset;
    g_Task->unk_09 += 1;
    timer         = g_Task->timer + 4;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 16) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF6E0(void) {
    s32 cosine;

    g_Task->unk_2E.value += (rsin(g_Task->unk_14) * 0x18) >> 0xC;
    cosine = rcos(g_Task->unk_14);
    g_Task->unk_30.value += FIXED_MUL(cosine, 0x18);
    g_Task->unk_09 += 1;
    if (g_Task->unk_09 == 0x14) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801EF7A8(void) {
    POLY_FT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_OVER_BATTLERS, tpage);
    g_ScratchPad.cells.words[0] = 0x4A;
    prim                        = (POLY_FT4*)g_GfxPrimCursor;
    g_ScratchPad.cells.words[2] = g_Task->timer * 8;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.words[1] = g_Task->unk_14 + 0xF78;
    setXY0(prim, g_Task->unk_2E.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]),
           g_Task->unk_30.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]));
    g_ScratchPad.cells.words[1] = g_Task->unk_14 + 0x888;
    prim->x1                    = g_Task->unk_2E.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    prim->y1                    = g_Task->unk_30.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    g_ScratchPad.cells.words[1] = g_Task->unk_14 + 0x88;
    prim->x2                    = g_Task->unk_2E.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    prim->y2                    = g_Task->unk_30.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    g_ScratchPad.cells.words[1] = g_Task->unk_14 + 0x773;
    prim->x3                    = g_Task->unk_2E.value + FIXED_MUL(rsin(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    prim->y3                    = g_Task->unk_30.value + FIXED_MUL(rcos(g_ScratchPad.cells.words[1]), g_ScratchPad.cells.words[0]);
    prim->tpage                 = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut                  = GetClut(g_Task->param.unk_0B, 506);
    setUV4(prim, 8, (g_Task->unk_09 & 3) * 32 + 8, 0x98, (g_Task->unk_09 & 3) * 32 + 8, 8, (g_Task->unk_09 & 3) * 32 + 0x28, 0x98, (g_Task->unk_09 & 3) * 32 + 0x28);
    setRGB0(prim, g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2], g_ScratchPad.cells.words[2]);
    GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_FT4));
}

/* func_801EFB78 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EFBDC */
#include "overlays/bmagic/shared/Actor_Clear.h"
