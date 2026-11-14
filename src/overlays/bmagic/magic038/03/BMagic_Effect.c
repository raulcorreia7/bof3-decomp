#include "magic038_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u16          i;
    u8           slot;
    PartyMember* task;
    PartyMember* work;
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;

    Battle_CenterCamera();
    task               = g_Task;
    task->param.unk_0B = 0;
    task->pos.z.fixed += TO_COORD(0x200);
    g_Task->unk_09 = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 16; i++) {
        slot                               = Battle_AllocEffect(1, 89);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    /* Copies the first two CLUTs of arena palette row 26 into the work copy as they are, then row 2 with STP set. */
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    i       = 0;
    row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    for (; i < 16; i++) {
        row_dst[i] = row_src[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                     = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE14(void) {
    u8           i;
    u8           slot;
    PartyMember* work;

    if (g_Task->param.unk_0B == 0) {
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 1));
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            for (i = 0; i < 8; i++) {
                if (!Battle_SlotIsBlocked((u8)(i + BATTLE_PARTY_CHARACTERS_COUNT))) {
                    slot                               = Battle_AllocEffect(1, 89);
                    work                               = g_Task;
                    g_BattleEffects[slot].header.mode  = 1;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].unk_04       = 2;
                    g_BattleEffects[slot].target.party = work;
                    g_BattleEffects[slot].pos.x        = g_BattleEnemyBattlers[i].pos.x;
                    g_BattleEffects[slot].pos.y        = g_BattleEnemyBattlers[i].pos.y;
                    g_BattleEffects[slot].pos.z        = g_BattleEnemyBattlers[i].pos.z;
                    g_Task->param.unk_0B += 1;
                }
            }
        } else {
            for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
                if (!Battle_SlotIsBlocked(i)) {
                    slot                               = Battle_AllocEffect(1, 89);
                    work                               = g_Task;
                    g_BattleEffects[slot].header.mode  = 1;
                    g_BattleEffects[slot].unk_04       = 2;
                    g_BattleEffects[slot].unk_03       = i;
                    g_BattleEffects[slot].target.party = work;
                    g_BattleEffects[slot].pos.x        = g_Game.members[i].pos.x;
                    g_BattleEffects[slot].pos.y        = g_Game.members[i].pos.y;
                    g_BattleEffects[slot].pos.z        = g_Game.members[i].pos.z;
                    g_Task->param.unk_0B += 1;
                }
            }
        }
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EF0D0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF114(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF9A8 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF1AC(void) {
    u8           timer;
    s8           tint;
    PartyMember* work;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_0C                   = 0;
        g_Task->unk_14                   = 0;
        D_1F800000.view.scenario.math_00 = (g_Task->unk_0C & 0x7F) << 5;
        g_Task->pos.x.fixed              = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(D_1F800000.view.scenario.math_00), 0x40000);
        g_Task->pos.y.fixed              = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(D_1F800000.view.scenario.math_00), 0x40000);
        D_1F800000.view.scenario.math_00 = (g_Task->unk_14 & 0x3F) << 6;
        g_Task->pos.z.fixed              = g_BattleEffectBattler->pos.z.fixed + FIXED_MUL(rsin(D_1F800000.view.scenario.math_00), 0x800000);
        g_Task->unk_25                   = 29;
        g_Task->unk_26                   = 0;
        g_Task->unk_27                   = 32;
        g_Task->unk_28                   = 0;
        g_Task->unk_24                   = 0;
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C    = 1;
        tint              = -0x80;
        g_Task->unk_5D    = tint;
        g_Task->unk_5E    = tint;
        g_Task->unk_5F    = tint;
        g_Task->unk_2A    = 0;
        g_Task->unk_29    = 4;
        work              = g_Task;
        work->unk_2B      = 0;
        work->unk_2C.half = 0;
        Actor_SelectScript(D_801EF9C0[g_Task->param.unk_0B]);
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF3BC);

/* Circles the effect round the battler on its two counters, bobbing it by a radius of 0x800, and at
 * the 256th step darkens it and advances the step. */
MATCH void func_801EF590(void) {
    PartyMember* work;
    s8           tint;

    Actor_StepAnimLoop();
    work                             = g_Task;
    D_1F800000.view.scenario.math_00 = (++work->unk_0C & 0x7F) << 5;
    g_Task->pos.x.fixed              = g_BattleEffectBattler->pos.x.fixed + FIXED_MUL(rsin(D_1F800000.view.scenario.math_00), 0x20000);
    g_Task->pos.y.fixed              = g_BattleEffectBattler->pos.y.fixed + FIXED_MUL(rcos(D_1F800000.view.scenario.math_00), 0x20000);
    work                             = g_Task;
    D_1F800000.view.scenario.math_00 = (++work->unk_14 & 0x3F) << 6;
    D_1F800000.view.scenario.math_04 = 0x800;
    g_Task->pos.z.fixed              = g_BattleEffectBattler->pos.z.fixed + rsin(D_1F800000.view.scenario.math_00) * D_1F800000.view.scenario.math_04;
    if (g_Task->unk_0C == 0x100) {
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C = 1;
        tint           = -0x40;
        g_Task->unk_5D = tint;
        g_Task->unk_5E = tint;
        g_Task->unk_5F = tint;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF710);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF8B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 11), 2, g_Task);
}

#include "overlays/bmagic/Effect_QueueEntry.h"

#include "overlays/bmagic/Effect_TickOnZeroTick.h"
