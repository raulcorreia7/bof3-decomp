#include "magic067_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic067Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EEC94);

#include "overlays/bmagic/Effect_CountDownTimerCallSelector.h"

MATCH void func_801EEFA4(void) {
    if (g_Task->param.phase == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF010(void) {
    u8 slot;
    u8 count;
    u8 battler;
    u8 i;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        if (g_Battle.target_selector & 0x40) {
            for (i = 0; i < 8; i++) {
                battler = i + BATTLE_PARTY_CHARACTERS_COUNT;
                if (!Battle_SlotIsBlocked(battler)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = g_Task;
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].pos.x.fixed  = g_BattleEnemyBattlers[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_BattleEnemyBattlers[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_BattleEnemyBattlers[i].pos.z.fixed;
                    g_Task->param.unk_0B += 1;
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!Battle_SlotIsBlocked(i)) {
                    slot                               = Battle_AllocEffect(1, 0x13);
                    g_BattleEffects[slot].target.party = g_Task;
                    g_BattleEffects[slot].header.mode  = 2;
                    g_BattleEffects[slot].unk_04       = 5;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].pos.x.fixed  = g_Game.members[i].pos.x.fixed;
                    g_BattleEffects[slot].pos.y.fixed  = g_Game.members[i].pos.y.fixed;
                    g_BattleEffects[slot].pos.z.fixed  = g_Game.members[i].pos.z.fixed;
                    g_Task->param.unk_0B += 1;
                }
            }
        }
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF2D0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF314(void) {
    SYS_DISPATCH_BYTE(D_801F04C8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetFacingMatrix();
        func_801EF79C();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EF38C);

MATCH void func_801EF44C(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    count_next     = g_Task->unk_09 + 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0xC0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF4F4(void) {
    s32 count;
    u8  count_next;

    count = g_Task->param.phase + 1;
    count += g_Task->unk_09 >> 6;
    g_Task->param.phase = count;
    if (g_FrameCount & 0x1) {
        g_Task->timer -= 1;
    }
    count_next     = g_Task->unk_09 - 2;
    g_Task->unk_09 = count_next;
    if ((count_next & BYTE_MASK) == 0x60) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_Drift.h"

#include "overlays/bmagic/Effect_SetFacingMatrix.h"

INCLUDE_ASM(func_801EF79C);

MATCH void func_801EFF24(void) {
    D_801F04D8[g_Task->header.step]();
    if (g_Task->header.flags != 0) {
        func_801F00C4();
    }
}

#include "overlays/bmagic/Effect_ArmCounterNextStep.h"

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_CountDownAndStep.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801F00C4(void) {
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(2, getTPage(0, 1, 320, 256));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_BattleEffectBattler->facing & 1) {
        setXYWH(prim, 0, 0, 319, 239);
    } else {
        setXY4(prim, 319, 0, 0, 0, 319, 239, 0, 239);
    }
    D_1F800000.view.effect.params[0] = g_Task->unk_09;
    D_1F800000.view.effect.params[1] = g_Task->unk_09 * 8;
    setRGB0(prim, prim->r3 = D_1F800000.view.effect.params[0], prim->g3 = D_1F800000.view.effect.params[0], prim->b3 = D_1F800000.view.effect.params[0]);
    setRGB1(prim, prim->r2 = D_1F800000.view.effect.params[1], prim->g2 = D_1F800000.view.effect.params[1], prim->b2 = D_1F800000.view.effect.params[1]);
    GFX_AddPrim(2, sizeof(POLY_G4));
    GFX_AddDitheredDrawMode(2, getTPage(0, 0, 320, 256));
}

MATCH void func_801F02A0(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 12, 2, g_Task);
}

#include "overlays/bmagic/Effect_QueueEntry.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801F038C(void) {
    Magic067SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
}

MATCH void func_801F03EC(void) {
    g_Task->param.phase = 0;
    g_Task->unk_09      = 0;
    Actor_SelectScript(3);
    g_Task->header.step++;
}

#include "overlays/bmagic/Effect_AddActor.h"

MATCH void func_801F0498(void) {
    func_801E5988();
}
