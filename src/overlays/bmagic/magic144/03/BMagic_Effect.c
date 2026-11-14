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
    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    actor                              = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 0x36) & BYTE_MASK;
    i                                  = 1;
    dst                                = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + 2);
    src                                = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW + 2);
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B               = 1;
    for (; i < 16; i++) {
        *dst++ = *src++ | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = 0;
    g_GfxPalettePending                                      = 1;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEE9C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEE0(void) {
    SYS_DISPATCH_BYTE(D_801F04D4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF294();
        PopMatrix();
    }
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
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
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

#include "overlays/bmagic/Effect_StepOnOwnTickFlag.h"

MATCH void func_801EF154(void) {
    u8 count;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = count - 1;
    }
    if (g_Task->param.unk_0B == 0x80) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF294(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = 0x180;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    if (g_Task->unk_09 < 16) {
        D_1F800000.view.effect.params[7] = g_Task->unk_09 << 3;
    } else {
        D_1F800000.view.effect.params[7] = 0x80;
    }

    for (i = 1; i < 9; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7], D_1F800000.view.effect.params[7]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
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

#include "overlays/bmagic/Effect_StartAtTarget.h"

MATCH void func_801EF654(void) {
    EFFECT_ADVANCE_AT_COUNT(4, 0x11);
}

#include "overlays/bmagic/Effect_CountUpAndMarkBattler.h"

#include "overlays/bmagic/Effect_CountDownByTwoFinishAtOne.h"

INCLUDE_ASM(func_801EF818);

MATCH void func_801EFF74(void) {
    PartyMember* work;
    u16          x;
    u16          y;

    SYS_DISPATCH_BYTE(D_801F04FC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        work = g_Task;
        if (work->param.unk_0B == 1) {
            x = work->unk_2E.half - MAGIC092_STEP_X;
            y = work->unk_30.half;
        } else {
            x = work->unk_2E.half + MAGIC092_STEP_X;
            y = work->unk_30.half;
        }
        y -= MAGIC092_RISE_Y;
        work->unk_2E.half = x;
        work->unk_30.half = y;
        func_801F01D0();
    }
}

#include "overlays/bmagic/Effect_AppearAtTarget.h"

MATCH void func_801F00A0(void) {
    EFFECT_ADVANCE_AT_COUNT(2, 0x10);
}

#include "overlays/bmagic/Effect_StepOnTickFlag.h"

#include "overlays/bmagic/Effect_TickCounter.h"

MATCH void func_801F01D0(void) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    D_1F800000.view.effect.params[0] = (rand() & 0xF) + 0x40;
    D_1F800000.view.effect.params[7] = g_Task->unk_09 * 10;
    for (i = 0; i < 8; i++) {
        if (GetGraphType() == 1 || GetGraphType() == 2) {
            tpage = 0xA5;
        } else {
            tpage = 0x35;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]),
               g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]), g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]),
               g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]));
        prim->r0 = D_1F800000.view.effect.params[7];
        prim->g0 = D_1F800000.view.effect.params[7] / 5;
        prim->b0 = D_1F800000.view.effect.params[7] / 5;
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

/* func_801F046C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
