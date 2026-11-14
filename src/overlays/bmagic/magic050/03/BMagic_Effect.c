#include "magic050_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC10 */
#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    u8           i;

    g_Task->param.unk_0B = 0;
    Battle_CenterCamera();
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->unk_09       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 4) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = work;
        g_BattleEffects[slot].arg.unk_09   = D_801EFA90[i] + 1;
        g_BattleEffects[slot].unk_08       = g_Task->facing;
        g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
        g_Task->param.unk_0B += 1;
        i++;
    } while (i < 10);
    SND_QueueSelectionEffect(0x100);
}

MATCH void func_801EEDF8(void) {
    s32 cue;
    s32 timer;
    u8  timer_next;

    timer = g_Task->unk_09;
    if (timer != 16) {
        if (timer < 17) {
            cue = 0x101;
            if (timer != 8) {
            } else {
                goto block_7;
            }
        } else {
            cue = 0x101;
            if (timer != 24) {
            } else {
                goto block_7;
            }
        }
    } else {
        cue = 0x102;
    block_7:
        SND_QueueSelectionEffect(cue);
    }
    timer_next     = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer_next;
    if ((timer_next & BYTE_MASK) == 25) {
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEF08 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF4C(void) {
    SYS_DISPATCH_BYTE(D_801EFAF0, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Battle_ProjectRange();
        func_801EF1B0();
        func_801EF4C4();
        func_801EF898();
    }
}

INCLUDE_ASM(func_801EEFDC);

#include "overlays/bmagic/Effect_CountUpTimerByTwoAndStep.h"

MATCH void func_801EF138(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->timer++;
    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF1B0);

INCLUDE_ASM(func_801EF4C4);

MATCH void func_801EF898(void) {
    TILE_1* prim;
    s32     i;
    s32     tpage;

    D_1F800000.view.scenario.math_00 = g_Task->timer * 3;
    D_1F800000.view.scenario.math_08 = g_Task->unk_09 * 6;
    D_1F800000.view.scenario.math_0C = g_Task->unk_09;
    for (i = 0; i < 16; i++) {
        if (GetGraphType() == 1 || GetGraphType() == 2) {
            tpage = 0xA5;
        } else {
            tpage = 0x35;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (TILE_1*)g_GfxPrimCursor;
        SetTile1(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), D_1F800000.view.scenario.math_00));
        if (g_Battle.action_id == 50) {
            prim->r0 = D_1F800000.view.scenario.math_08;
            prim->g0 = D_1F800000.view.scenario.math_08;
            prim->b0 = D_1F800000.view.scenario.math_0C;
        } else {
            prim->r0 = D_1F800000.view.scenario.math_08;
            prim->g0 = D_1F800000.view.scenario.math_0C;
            prim->b0 = D_1F800000.view.scenario.math_08;
        }
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(TILE_1));
    }
}
