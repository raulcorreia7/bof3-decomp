#include "magic021_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    Magic021Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EFE14[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EFE14[i];
            g_BattleEffectBattler = D_801EFE14[i].target.party;
            func_801EF534();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED30(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u32           i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    func_800AEF98(0xC, 2);
    index  = Battle_AllocEffect(1, 9) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* row;

        row                     = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index];
        *(BattleWorkImage*)slot = *row;
    } else {
        BattleWorkImage* row;
        u32              enemy;

        slot                    = &g_BattleEffects[index];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        row                     = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *row;
    }
    work                                 = g_Task;
    g_BattleEffects[index].unk_06        = 1;
    g_BattleEffects[index].header.mode   = 0;
    g_BattleEffects[index].header.step   = 0;
    g_BattleEffects[index].handler_index = 9;
    g_BattleEffects[index].target.party  = work;
    g_Task->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

#include "overlays/bmagic/Effect_ReleaseActiveBattlerOnTickerZero.h"

#include "shared/Effect_StartPlaying.h"

/* func_801EEFDC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF020(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF104(void) {
    PartyMember* work;
    u32          slot;
    u8           i;
    u8           timer;

    Actor_StepAnimOnce();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer != 0) {
        return;
    }
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09       = 0;
    g_Task->param.unk_0B = 0;
    for (i = 0; i < 12; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        work                                   = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i >> 1) * 3 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    g_Task->header.step += 1;
}

MATCH void func_801EF208(void) {
    if (Actor_StepAnimOnce() != 0u) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF260(void) {
    if ((u8)g_Task->unk_09 < 0xCU) {
        Effect_DrawScreenFade();
        g_Task->unk_09 += 4;
        return;
    }
    g_Task->header.step += 1;
}

MATCH void func_801EF2CC(void) {
    if (g_Task->param.unk_0B == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF328(void) {
    func_801E5988();
}

#include "overlays/bmagic/Effect_DrawScreenFade.h"

MATCH void func_801EF534(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Task);
}

MATCH void func_801EF578(void) {
    SYS_DISPATCH_BYTE(D_801EFE08, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EF7FC();
        func_801EFA48();
    }
}

MATCH void func_801EF600(void) {
    PartyMember* actor;
    PartyMember* work;
    s16*         radius_cell;
    u32          offset;
    u16          phase;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        offset                 = rand() & 0x7;
        actor                  = g_BattleSelectedActor;
        work                   = g_Task;
        work->pos.x.fixed      = actor->pos.x.fixed;
        work->pos.y.fixed      = actor->pos.y.fixed;
        COORD_INT(work->pos.z) = (s16)((u16)COORD_INT(actor->pos.z) + (offset << 5));
        radius_cell            = &D_1F800000_HALF;
        *radius_cell           = 0xC0 - (offset << 4);
        phase                  = rand() & 0x7;
        D_1F800004             = phase << 9;
        g_Task->pos.x.fixed += (rsin(phase << 9) * *radius_cell) >> 3;
        FAKE_BARRIER(); /* FAKE: keeps the angle load after the x update, as retail does. */
        g_Task->pos.y.fixed += (rcos(D_1F800004) * *radius_cell) >> 3;
        g_Task->unk_09 = 0;
        g_Task->timer  = 16;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpByTwoAndStep.h"

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    work        = g_Task;
    work->timer = work->timer - 2;
    if (work->timer == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EF7FC);

/* Draw the magic021 ring as sixteen shaded quads between two radii around the effect,
 * tinted on the inner edge by the timer and dark on the outer one. */
MATCH void func_801EFA48(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    u8       red;
    u8       green;
    u8       blue;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    i = 0;
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[2] = 0;
    red                              = g_Task->timer * 12;
    green                            = g_Task->timer * 6;
    blue                             = g_Task->timer * 4;
    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 2;
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 3;
    D_1F800000.view.effect.params[4] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[5] = g_Task->unk_30.half;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y0                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x2                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
        prim->y2                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
        D_1F800000.view.effect.params[2] = (i + 1) << 8;
        prim->x1                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->y1                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        prim->x3                         = D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
        prim->y3                         = D_1F800000.view.effect.params[5] + FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
        prim->r0                         = red;
        prim->g0                         = green;
        prim->b0                         = blue;
        prim->r1                         = red;
        prim->g1                         = green;
        prim->b1                         = blue;
        prim->r2                         = 1;
        prim->g2                         = 1;
        prim->b2                         = 1;
        prim->r3                         = 1;
        prim->g3                         = 1;
        prim->b3                         = 1;
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

/* func_801EFD4C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFDB0 */
#include "overlays/bmagic/Actor_Clear.h"
