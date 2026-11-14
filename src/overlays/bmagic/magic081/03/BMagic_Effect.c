#include "magic081_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(SAVE_AccessFile);

INCLUDE_ASM(func_801EED44);

MATCH void func_801EEE74(void) {
    PartyMember* saved;

    saved  = g_Task;
    g_Task = D_801EC2E0->target.party;
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        saved->header.mode++;
    }
    g_Task = saved;
}

INCLUDE_ASM(func_801EEEDC);

MATCH void func_801EEF88(void) {
    PartyMember* saved_work;

    saved_work = g_Task;
    g_Task     = D_801EC2E0->target.party;
    Actor_StepAnimOnce();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF014 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF058(void) {
    Magic081Steps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF0B8(void) {
    u32          slot;
    u8           effect_index;
    PartyMember* task;

    g_Task->pos.x.fixed                        = g_BattleEffectBattler->pos.x.fixed + TO_COORD(2);
    g_Task->pos.y.fixed                        = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(g_Task->pos.z)                   = COORD_INT(g_BattleEffectBattler->pos.z);
    slot                                       = Battle_AllocEffect(1, 66);
    effect_index                               = slot & BYTE_MASK;
    task                                       = g_Task;
    g_BattleEffects[effect_index].header.mode  = 1;
    g_BattleEffects[effect_index].target.party = task;
    g_Task->timer                              = slot;
    SND_QueueSelectionEffect(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF18C(void) {
    u8 slot;
    u8 tick;

    if ((g_FrameCount & 0x3) == 0x3) {
        slot                                   = BMagic_AllocEffect();
        BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = g_Task->unk_09;
        tick                                   = g_Task->unk_09;
        if (tick < 100) {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8;
        } else {
            BMAGIC_EFFECT_SLOTS[slot].unk_0A = 8 - (tick - 100) / 4;
        }
        g_Task->param.unk_0B += 1;
    }
    tick           = g_Task->unk_09 + 1;
    g_Task->unk_09 = tick;
    if (tick >= 129U) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF2F0(void) {
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        func_801E5988();
    } else {
        Battle_CenterCamera();
    }
}

MATCH void func_801EF330(void) {
    Magic081SecondSteps handlers;

    handlers = D_801EEC20;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF39C(void) {
    u8 effect_slot;

    g_Task->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed + TO_COORD(1) / 8;
    g_Task->pos.y.fixed      = g_BattleEffectBattler->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 256;
    effect_slot              = g_BattleEffectBattler->timer;
    g_Task->unk_14           = ratan2(g_BattleEffects[effect_slot].pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffects[effect_slot].pos.y.fixed - g_Task->pos.y.fixed);
    g_Task->unk_09           = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF44C(void) {
    s32 angle;
    s32 phase;
    u8  count;

    phase          = (g_Task->unk_09 + g_Task->param.unk_0B) & 0x3F;
    SP_REF(s16, 2) = BMAGIC_PHASE_ANGLE(phase);
    angle          = g_Task->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    g_Task->unk_0C = angle;
    g_Task->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF6A0();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->timer = 64;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF57C);

MATCH void func_801EF614(void) {
    Battle_ProjectRange();
    func_801EF6A0();
    BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
    g_Task->header.flags = 0;
    g_Task->header.mode  = 0;
    g_Task->header.step  = 0;
    g_Task->unk_03       = 0;
    g_Task->unk_04       = 0;
}

/* Draws the effect glow as one textured quad around its screen point; the radius grows with the timer up to 0x40. */
MATCH void func_801EF6A0(void) {
    POLY_GT4* prim;
    s16*      shade;
    s32       tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x125 : 0x55;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    if (g_Task->unk_09 < 8) {
        D_1F800000.view.effect.params[0] = (g_Task->unk_09 + 1) * 8;
    } else {
        D_1F800000.view.effect.params[0] = 0x40;
    }
    shade                            = &D_1F800000.view.effect.params[4];
    *shade                           = 0x80;
    D_1F800000.view.effect.params[2] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[3] = g_Task->unk_30.half;
    setXY4(prim, D_1F800000.view.effect.params[2] + FIXED_MUL(rsin(0xC00), D_1F800000.view.effect.params[0]),
           D_1F800000.view.effect.params[3] + FIXED_MUL(rcos(0xC00), D_1F800000.view.effect.params[0]), D_1F800000.view.effect.params[2] + FIXED_MUL(rsin(0x800), D_1F800000.view.effect.params[0]),
           D_1F800000.view.effect.params[3] + FIXED_MUL(rcos(0x800), D_1F800000.view.effect.params[0]), D_1F800000.view.effect.params[2] + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]),
           D_1F800000.view.effect.params[3] + FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]), D_1F800000.view.effect.params[2] + FIXED_MUL(rsin(0x400), D_1F800000.view.effect.params[0]),
           D_1F800000.view.effect.params[3] + FIXED_MUL(rcos(0x400), D_1F800000.view.effect.params[0]));
    prim->tpage = GetTPage(0, 2, 832, 256);
    prim->clut  = GetClut(0, 506);
    prim->u0    = 1;
    prim->v0    = 1;
    prim->u1    = 31;
    prim->v1    = 1;
    prim->u2    = 1;
    prim->v2    = 31;
    prim->u3    = 31;
    prim->v3    = 31;
    prim->r0    = *shade;
    prim->g0    = *shade;
    prim->b0    = *shade;
    prim->r1    = *shade;
    prim->g1    = *shade;
    prim->b1    = *shade;
    prim->r2    = *shade;
    prim->g2    = *shade;
    prim->b2    = *shade;
    prim->r3    = *shade;
    prim->g3    = *shade;
    prim->b3    = *shade;
    SetSemiTrans(prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_GT4));
}

/* func_801EFA20 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
