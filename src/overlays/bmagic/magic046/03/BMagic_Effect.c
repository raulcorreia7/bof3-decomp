#include "magic046_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED28, Effect_PlayOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EFF3C[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EFF3C[i];
            g_BattleEffectBattler = D_801EFF3C[i].target.party;
            func_801EF324();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED28);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF70 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFB4(void) {
    /* Retail dispatches a stack copy of the handlers. */
    MagicModuleSteps handlers;

    handlers = D_801EEC00.steps;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801EF014(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    g_Task->facing     = g_BattleEffectBattler->facing;
    work               = g_Task;
    actor              = g_BattleEffectBattler;
    work->pos.x.fixed  = actor->pos.x.fixed;
    work->pos.y.fixed  = actor->pos.y.fixed;
    z                  = actor->pos.z.fixed;
    work->param.unk_0B = 0;
    work->pos.z.fixed  = z;
    g_Task->unk_09     = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801EF090);

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

#include "overlays/bmagic/Effect_DispatchStep.h"

MATCH void func_801EF250(void) {
    g_Task                           = g_BattleEffectBattler;
    BATTLE_ACTIVE_WORK->param.unk_0B = 0;
    g_Task->unk_09                   = 0;
    Actor_SelectScript(2U);
    g_Task->header.mode = 1;
    g_Task->header.step = 1;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801EF304(void) {
    func_801E5988();
}

MATCH void func_801EF324(void) {
    /* Retail dispatches a stack copy of the handlers. */
    Magic046Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_801EFB90();
        func_801EFC48();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF3B8);

MATCH void func_801EF540(void) {
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
    func_801EF7E8();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF660(void) {
    s32 angle;
    s32 phase;
    u8  timer_next;

    phase          = (g_Task->unk_09 + g_Task->param.unk_0B) & 0x3F;
    SP_REF(s16, 2) = BMAGIC_PHASE_ANGLE(phase);
    angle          = g_Task->unk_14 + ((rsin((s16)BMAGIC_PHASE_ANGLE(phase)) * 0x12C) >> 0xC);
    g_Task->unk_0C = angle;
    g_Task->pos.x.fixed += (rsin(angle) * 0x7000) >> 0xC;
    g_Task->pos.y.fixed += (rcos(g_Task->unk_0C) * 0x7000) >> 0xC;
    Battle_ProjectRange();
    func_801EF7E8();
    g_Task->unk_09 += 1;
    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.flags = 0;
        g_Task->header.mode  = 0;
        g_Task->header.step  = 0;
        g_Task->unk_03       = 0;
        g_Task->unk_04       = 0;
    }
}

INCLUDE_ASM(func_801EF7E8);

MATCH void func_801EFB90(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(BATTLE_ACTIVE_WORK);
}

MATCH void func_801EFC48(void) {
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
    D_1F800000.view.effect.params[0] = (g_Task->unk_09 + 6) * 10;
    D_1F800000.view.effect.params[4] = g_Task->timer * 6;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);

    for (i = 1; i <= 8; i++) {
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
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[4]);
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

/* func_801EFED0 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
