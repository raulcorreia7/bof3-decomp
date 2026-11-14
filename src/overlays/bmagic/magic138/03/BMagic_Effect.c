#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC88);

MATCH void func_801EED60(void) {
    PartyMember* saved;
    u8           slot;

    if ((g_FrameCount & 7) == 0) {
        slot = Battle_AllocEffect(1, 0x56);
        if (slot != 0xFF) {
            g_BattleEffects[slot].header.mode = 0;
            g_BattleEffects[slot].header.step = 0;
            g_BattleEffects[slot].unk_2E      = 220;
            g_BattleEffects[slot].unk_30      = 250;
            if (g_Task->unk_09 & 1) {
                g_BattleEffects[slot].unk_2E += 20;
            }
            g_BattleEffects[slot].unk_0A       = g_Task->unk_09;
            g_BattleEffects[slot].target.party = g_Task;
            g_Task->unk_09 += 1;
            g_Task->param.unk_0B += 1;
        }
        if (g_Task->unk_09 == 6) {
            g_Task->header.mode += 1;
        }
        saved  = g_Task;
        g_Task = g_BattleEffectBattler;
        Actor_StepAnimLoop();
        g_Task = saved;
    }
}

MATCH void func_801EEED8(void) {
    PartyMember* saved_work;

    saved_work = g_Task;
    g_Task     = g_BattleEffectBattler;
    Actor_StepAnimLoop();
    g_Task = saved_work;
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEF60 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA4(void) {
    Magic138Steps handlers;

    handlers      = D_801EEC10;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Task);
    if (g_Task->header.flags & 0x1) {
        Area_AddActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF04C(void) {
    s32 left;

    if (g_Battle.active_battler < 3) {
        if (g_BattleEffectBattler->unk_09 & 1) {
            left           = g_Task->unk_2E.signed_half - 40;
            g_Task->unk_0C = ((g_Game.members[g_Battle.active_battler].unk_2E.signed_half - left) << 4) / 8;
            g_Task->unk_10 = ((g_Game.members[g_Battle.active_battler].unk_30.signed_half - g_Task->unk_30.signed_half) << 4) / 8;
        } else {
            left           = g_Task->unk_2E.signed_half - 20;
            g_Task->unk_0C = ((g_Game.members[g_Battle.active_battler].unk_2E.signed_half - left) << 4) / 8;
            g_Task->unk_10 = ((g_Game.members[g_Battle.active_battler].unk_30.signed_half - g_Task->unk_30.signed_half) << 4) / 8;
        }
    } else {
        if (g_BattleEffectBattler->unk_09 & 1) {
            left           = g_Task->unk_2E.signed_half - 40;
            g_Task->unk_0C = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].unk_2E - left) << 4) / 8;
            g_Task->unk_10 = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].unk_30 - g_Task->unk_30.signed_half) << 4) / 8;
        } else {
            left           = g_Task->unk_2E.signed_half - 20;
            g_Task->unk_0C = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].unk_2E - left) << 4) / 8;
            g_Task->unk_10 = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].unk_30 - g_Task->unk_30.signed_half) << 4) / 8;
        }
    }
    g_Task->unk_18      = g_Task->unk_2E.signed_half << 4;
    g_Task->unk_1C      = g_Task->unk_30.signed_half << 4;
    g_Task->unk_25      = 30;
    g_Task->unk_26      = 0;
    g_Task->unk_48      = 1;
    g_Task->unk_27      = 0xA0;
    g_Task->unk_28      = 0;
    g_Task->unk_24      = 0x84;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 3;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    Actor_SelectScript((g_Battle.target_selector - 3) & 1);
    g_Task->unk_09 = 3;
    g_Task->header.step += 1;
}

MATCH void func_801EF3A0(void) {
    u8 slot;

    g_Task->unk_2E.half = g_Task->unk_18 >> 4;
    g_Task->unk_30.half = g_Task->unk_1C >> 4;
    g_Task->unk_18 += g_Task->unk_0C;
    g_Task->unk_1C += g_Task->unk_10;
    if (g_Battle.active_battler < 3) {
        if (g_Task->unk_30.signed_half < g_Game.members[g_Battle.active_battler].unk_30.signed_half - 20) {
            slot                               = Battle_AllocEffect(1, 0x56);
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].header.step  = 0;
            g_BattleEffects[slot].unk_2E       = g_Task->unk_2E.half;
            g_BattleEffects[slot].unk_30       = g_Task->unk_30.half;
            g_BattleEffects[slot].unk_0A       = g_Task->timer;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_Task->header.step += 1;
        }
    } else {
        if (g_Task->unk_30.signed_half < g_BattleEnemyBattlers[g_Battle.active_battler - 3].unk_30 - 40) {
            slot                               = Battle_AllocEffect(1, 0x56);
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].header.step  = 0;
            g_BattleEffects[slot].unk_2E       = g_Task->unk_2E.half;
            g_BattleEffects[slot].unk_30       = g_Task->unk_30.half;
            g_BattleEffects[slot].unk_0A       = g_Task->timer;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_Task->header.step += 1;
        }
    }
    Actor_StepAnimLoop();
}

MATCH void func_801EF50C(void) {
    func_801E5988();
}

MATCH void func_801EF52C(void) {
    Magic138Steps handlers;

    handlers      = D_801EEC1C;
    g_Scripts = BATTLE_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5D0(void) {
    PartyMember* work;
    g_Task->unk_29    = 0;
    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    g_Task->unk_24    = 0x84;
    g_Task->unk_27    = 0xB4;
    g_Task->unk_28    = 0;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    g_Task->unk_2A    = 0;
    Actor_SelectScript(5);
    SND_PlayCue((g_Task->timer & 0x1) | 0x100);
    g_Task->header.step += 1;
}

MATCH void func_801EF6A4(void) {
    if (Actor_StepAnimLoop() != 0u) {
        g_Task->header.step = g_Task->header.step + 1;
    } else {
        Area_AddActor();
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"
