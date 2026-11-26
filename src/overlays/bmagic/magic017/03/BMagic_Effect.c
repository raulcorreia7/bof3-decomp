#include "magic017_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC98(void) {
    PartyMember* work;
    u32          index;
    u8           i;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&TASK(PartyMember)->pos, &g_BattleEffectBattler->pos);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 0);
    for (i = 0; i < 6; i++) {
        index = Battle_AllocEffect(1, 33);
        Effect_CopyActiveBattlerToSlot(index);
        work                                            = TASK(PartyMember);
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].effect_type  = 33;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = (i & 0xFE) + 1;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        TASK(PartyMember)->param.unk_0B++;
    }
    TASK(PartyMember)->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    TASK(PartyMember)->unk_28 = g_BattleEffectBattler->unk_28;
    TASK(PartyMember)->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(TASK(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_ReleaseActiveBattlerOnTickerZero.h"

MATCH void func_801EEFD8(void) {
    u16* flags;

    func_800AFC54();
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
    Effect_Reset();
}

/* func_801EF014 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF058(void) {
    Magic017Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF11C(void) {
    s8 tint;
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count != 0) {
        return;
    }
    TASK(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                      = -64;
    TASK(PartyMember)->unk_5C = 1;
    TASK(PartyMember)->unk_2B = 1;
    TASK(PartyMember)->unk_5D = tint;
    TASK(PartyMember)->unk_5E = tint;
    TASK(PartyMember)->unk_5F = tint;
    TASK(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    if ((TASK(PartyMember)->param.unk_0B & 1) == 0) {
        TASK(PartyMember)->unk_0C = 0;
        TASK(PartyMember)->unk_10 = -ONE;
    } else {
        TASK(PartyMember)->unk_0C = 0;
        TASK(PartyMember)->unk_10 = ONE;
    }
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->unk_09 = 16;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF248(void) {
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    TASK(PartyMember)->unk_5D -= 4;
    TASK(PartyMember)->unk_5E -= 4;
    TASK(PartyMember)->unk_5F -= 4;
    if (--TASK(PartyMember)->unk_09 == 0) {
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF300(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) != 0x10) {
        return;
    }
    if ((TASK(PartyMember)->param.unk_0B & 1) != 0) {
        TASK(PartyMember)->unk_0C = -0x20000;
        TASK(PartyMember)->unk_10 = -0x10000;
    } else {
        TASK(PartyMember)->unk_0C = -0x20000;
        TASK(PartyMember)->unk_10 = 0x10000;
    }
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed + TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed + TASK(PartyMember)->unk_10;
    TASK(PartyMember)->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
    if ((TASK(PartyMember)->param.unk_0B & 1) != 0) {
        TASK(PartyMember)->unk_0C = 0;
        TASK(PartyMember)->unk_10 = 0x1000;
    } else {
        TASK(PartyMember)->unk_0C = 0;
        TASK(PartyMember)->unk_10 = -0x1000;
    }
    Effect_RotatePosition(g_Task);
    if (TASK(PartyMember)->param.unk_0B == 0) {
        SND_SEQueueSelection(0x101);
    }
    TASK(PartyMember)->unk_09 = 0x10;
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF460(void) {
    PartyMember* task;
    u8           timer;

    task = TASK(PartyMember);
    task->pos.x.fixed += task->unk_0C;
    task->unk_5D += 4;
    task->pos.y.fixed += task->unk_10;
    TASK(PartyMember)->unk_5E += 4;
    TASK(PartyMember)->unk_5F += 4;
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        if (TASK(PartyMember)->param.unk_0B == 0) {
            TASK(PartyMember)->header.flags &= 0xDF;
            TASK(PartyMember)->unk_5C = 0;
            TASK(PartyMember)->unk_2B = 0;
            TASK(PartyMember)->unk_5D = 0;
            TASK(PartyMember)->unk_5E = 0;
            TASK(PartyMember)->unk_5F = 0;
            if (g_Battle.active_battler >= 3) {
                func_801E257C(g_Battle.active_battler, 2);
            }
            TASK(PartyMember)->unk_09 = func_800AFF98();
            TASK(PartyMember)->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF5FC(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->param.unk_0B == 1) {
        Script_AnimStepOnce();
        counter                   = TASK(PartyMember)->unk_09 - 1;
        TASK(PartyMember)->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            Battle_MarkDamaged(g_Battle.target_selector);
            Battle_PlayActiveBattlerSE(2, 4);
            TASK(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF694(void) {
    if (Script_AnimStepOnce() != 0u) {
        TASK(PartyMember)->unk_09      = 8;
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF6EC(void) {
    s8 tone;
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        if (g_Battle.active_battler >= 3U) {
            func_801E257C(g_Battle.active_battler, 0);
        }
        TASK(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        TASK(PartyMember)->unk_5C = 1;
        TASK(PartyMember)->unk_2B = 1;
        tone                      = -0x40;
        TASK(PartyMember)->unk_5D = tone;
        TASK(PartyMember)->unk_5E = tone;
        TASK(PartyMember)->unk_5F = tone;
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF7E0(void) {
    u8 timer;

    TASK(PartyMember)->unk_5D -= 8;
    TASK(PartyMember)->unk_5E -= 8;
    TASK(PartyMember)->unk_5F -= 8;
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        TASK(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        TASK(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        TASK(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        TASK(PartyMember)->unk_09      = 8;
        TASK(PartyMember)->header.step++;
    }
}

MATCH void func_801EF8B4(void) {
    u8 count;

    TASK(PartyMember)->unk_5D += 8;
    TASK(PartyMember)->unk_5E += 8;
    TASK(PartyMember)->unk_5F += 8;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF970(void) {
    Effect_Reset();
}
