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

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

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

MATCH void func_801EEFDC(void) {
    PartyMember* work;
    PartyMember* next;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        next         = g_Task;
        next->unk_0C = D_801EFAA0[next->param.unk_0B].x;
        next->unk_10 = D_801EFAA0[next->param.unk_0B].y;
        func_801DD350(next);
        work              = g_Task;
        work->pos.x.fixed = g_AreaScrollTargetX + work->unk_0C;
        work->pos.y.fixed = g_AreaScrollTargetY + work->unk_10;
        if (work->param.unk_0B == 0) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
        g_Task->unk_09 = 32;
        g_Task->timer  = 2;
        g_Task->header.step += 1;
    }
}

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

#ifdef NON_MATCHING
NON_MATCHING void func_801EF1B0(void) {
    POLY_G3*            prim;
    ScratchPadScenario* spad;
    s32                 i;
    s32                 tpage;

    D_1F800000.view.scenario.math_00 = g_Task->timer;
    if (g_Battle.action_id == 50) {
        D_1F800000.view.scenario.math_08 = g_Task->unk_09 * 3;
    } else {
        D_1F800000.view.scenario.math_08 = g_Task->unk_09 * 5;
    }
    D_1F800000.view.scenario.math_0C = g_Task->unk_09;
    spad                             = &D_1F800000.view.scenario;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), spad->math_00), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), spad->math_00),
               g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 8), spad->math_00), g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 8), spad->math_00));
        if (g_Battle.action_id == 50) {
            setRGB0(prim, spad->math_0C, spad->math_08, spad->math_08);
            setRGB1(prim, spad->math_08, spad->math_08, 1);
            setRGB2(prim, spad->math_08, spad->math_08, 1);
        } else {
            setRGB0(prim, spad->math_0C, 1, spad->math_08);
            setRGB1(prim, spad->math_08, spad->math_0C, spad->math_08);
            setRGB2(prim, spad->math_08, spad->math_0C, spad->math_08);
        }
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
#else
INCLUDE_ASM(func_801EF1B0);
#endif

INCLUDE_ASM(func_801EF4C4);

MATCH void func_801EF898(void) {
    TILE_1* prim;
    s32     i;
    s32     tpage;

    D_1F800000.view.scenario.math_00 = g_Task->timer * 3;
    D_1F800000.view.scenario.math_08 = g_Task->unk_09 * 6;
    D_1F800000.view.scenario.math_0C = g_Task->unk_09;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (TILE_1*)g_GfxPrimCursor;
        SetTile1(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), D_1F800000.view.scenario.math_00), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), D_1F800000.view.scenario.math_00));
        if (g_Battle.action_id == 50) {
            setRGB0(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_0C);
        } else {
            setRGB0(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_0C, D_1F800000.view.scenario.math_08);
        }
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(TILE_1));
    }
}
