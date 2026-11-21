#include "magic144_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_StartOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F050C[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F050C[i];
            g_BattleEffectBattler = D_801F050C[i].target.party;
            func_801EF510();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED04(void) {
    PartyMember* actor;
    PartyMember* task;
    u32          i;
    u32          slot;
    u16*         src;
    u16*         dst;

    g_Task->param.unk_0B = 0;
    BMAGIC_CLEAR_EFFECTS(i);
    actor                              = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 0x36) & BYTE_MASK;
    i                                  = 1;
    dst                                = BATTLE_EFFECT_PALETTE_COLORS;
    src                                = BATTLE_PALETTE_SOURCE_COLORS;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B               = 1;
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)) = 0;
    g_GfxPalettePending                                               = 1;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEE9C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE0(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F04D4, func_801EF294);
}

MATCH void func_801EEF68(void) {
    PartyMember* work;
    u8           i;
    u8           slot;

    g_Task->unk_09       = 0;
    g_Task->param.unk_0B = 0;
    for (i = 0; i < 3; i++) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            work                                  = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode = i != 0;
            BMAGIC_EFFECT_SLOTS[slot].header.step = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B      = i;
            BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            g_Task->param.unk_0B += 1;
        }
    }
    SND_QueueSelectionSE(EMI_SE_ID(SND_BANK_COMMON, 0x00));
    g_Task->header.step += 1;
}

MATCH void func_801EF078(void) {
    u8            timer;
    PartyMember** actor;
    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        actor = &g_Battle.selected_actor;
        GFX_FreePaletteFadeTarget(*actor);
        GFX_AllocPaletteFade(*actor, -8, -8, -8, 1);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF154(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EF294(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = 0x180;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    if (g_Task->unk_09 < 16) {
        g_ScratchPad.cells.halves[7] = g_Task->unk_09 << 3;
    } else {
        g_ScratchPad.cells.halves[7] = 0x80;
    }

    for (i = 1; i < 9; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EF510(void) {
    SYS_DISPATCH_TASK(D_801F04E4, 1, g_Task);
}

MATCH void func_801EF554(void) {
    SYS_DISPATCH_BYTE(D_801F04EC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF818();
    }
}

#include "overlays/bmagic/shared/Effect_StartAtTarget.h"

MATCH void func_801EF654(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/shared/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/shared/Effect_CountDownByTwoFinishAtOne.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF818(void) {
}
#else
INCLUDE_ASM(func_801EF818);
#endif

MATCH void func_801EFF74(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(D_801F04FC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        work = g_Task;
        if (work->param.unk_0B == 1) {
            x = work->unk_2E.value - MAGIC092_STEP_X;
            y = work->unk_30.value;
        } else {
            x = work->unk_2E.value + MAGIC092_STEP_X;
            y = work->unk_30.value;
        }
        y -= MAGIC092_RISE_Y;
        work->unk_2E.value = x;
        work->unk_30.value = y;
        func_801F01D0();
    }
}

#include "overlays/bmagic/shared/Effect_AppearAtTarget.h"

MATCH void func_801F00A0(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/shared/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/shared/Effect_TickCounter.h"

MATCH void func_801F01D0(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = (rand() & 0xF) + 0x40;
    g_ScratchPad.cells.halves[7] = g_Task->unk_09 * 10;
    for (i = 0; i < 8; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.value, g_Task->unk_30.value, g_Task->unk_2E.value + FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), g_Task->unk_2E.value + FIXED_MUL(rsin((i + 1) << 9), g_ScratchPad.cells.halves[0]),
               g_Task->unk_30.value + FIXED_MUL(rcos((i + 1) << 9), g_ScratchPad.cells.halves[0]));
        setRGB0(prim, g_ScratchPad.cells.halves[7], g_ScratchPad.cells.halves[7] / 5, g_ScratchPad.cells.halves[7] / 5);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* func_801F046C */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
