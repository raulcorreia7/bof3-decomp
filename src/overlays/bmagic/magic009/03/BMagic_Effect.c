#include "magic009_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC28.h"

MATCH void func_801EEC98(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u16*          dst;
    u16*          src;
    u32           index;
    u32           i;
    u8            active;

    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        g_Game.members[active].unk_4B = 0xFF;
    } else {
        g_BattleEnemyBattlers[active - BATTLE_PARTY_CHARACTERS_COUNT].unk_4B = 0xFF;
    }
    func_800AEF98(0x2C, 6);
    index  = Battle_AllocEffect(1, 42) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* row;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        row                     = (BattleWorkImage*)&g_Game.members[active];
        *(BattleWorkImage*)slot = *row;
    } else {
        BattleWorkImage* row;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        row                     = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *row;
    }
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 1;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 42;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_Task->param.unk_0B += 1;
    i   = 1;
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 0x3402u);
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 0x3402u);
    for (; i < 16; i++) {
        dst[0x20] = src[0x20] | 0x8000;
        src++;
        dst++;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 0x3440u) = 0;
    g_GfxPalettePending                        = 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEF08(void) {
    u32 slot;
    u32 i;

    if (g_Task->param.unk_0B == 0) {
        i = 0;
        do {
            slot                               = Battle_AllocEffect(1, 42) & BYTE_MASK;
            g_BattleEffects[slot].target.party = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 4 + 1;
            g_Task->param.unk_0B += 1;
            i++;
        } while (i < 3);
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

MATCH void func_801EF09C(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 0x2004;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    func_801E5988();
}

/* func_801EF0DC */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF120(void) {
    SYS_DISPATCH_BYTE(D_801EF8A4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF3B8();
    }
}

MATCH void func_801EF198(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        actor          = g_BattleSelectedActor;
        g_Task->facing = actor->facing;
        work           = g_Task;
        work->unk_0C   = D_801EF8B0[work->param.unk_0B].x;
        work->unk_10   = D_801EF8B0[work->param.unk_0B].y;
        func_801DD350(work);
        g_Task->pos.x.fixed = actor->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = actor->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = actor->pos.z.fixed + D_801EF8B0[g_Task->param.unk_0B].z;
        func_800AF764();
        g_Task->timer = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

/* func_801EF340 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

MATCH void func_801EF3B8(void) {
    POLY_FT4* prim;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.scenario.math_00 = g_Task->unk_09 << 1;
    prim                             = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.view.scenario.math_00),
           g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.view.scenario.math_00),
           g_Task->unk_2E.half + FIXED_MUL(rcos(3584), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rsin(3584), D_1F800000.view.scenario.math_00),
           g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.view.scenario.math_00));
    prim->tpage = GetTPage(0, 1, 832, 256);
    prim->clut  = GetClut(32, 506);
    prim->u0    = 128;
    prim->v0    = 32;
    prim->u1    = 160;
    prim->v1    = 32;
    prim->u2    = 128;
    prim->v2    = 64;
    prim->u3    = 160;
    prim->v3    = 64;
    prim->r0    = g_Task->timer * 10;
    prim->g0    = 0;
    prim->b0    = g_Task->timer * 9;
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

MATCH void func_801EF6B0(void) {
    Magic009Steps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF788(void) {
    u8 timer;
    u8 next;

    timer = g_Task->unk_09;
    if ((timer & BYTE_MASK) != 0xFF) {
        next           = timer - 1;
        g_Task->unk_09 = next;
        if (!(next & BYTE_MASK)) {
            func_800AFC98(2, 5);
        }
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF814(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF87C(void) {
    func_801E5988();
}
