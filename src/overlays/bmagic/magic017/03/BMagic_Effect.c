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

    BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&BMAGIC_WORK->pos, &g_BattleEffectBattler->pos);
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 0);
    for (i = 0; i < 6; i++) {
        index = Battle_AllocEffect(1, 33);
        Effect_CopyActiveBattlerToSlot(index);
        work                                            = g_Task;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].step_index   = 33;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = (i & 0xFE) + 1;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        BMAGIC_WORK->param.unk_0B++;
    }
    BMAGIC_WORK->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    BMAGIC_WORK->unk_28 = g_BattleEffectBattler->unk_28;
    BMAGIC_WORK->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
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
    SYS_DISPATCH_BYTE(handlers.steps, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF11C(void) {
    s8 tint;
    u8 count;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count != 0) {
        return;
    }
    BMAGIC_WORK->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                = -64;
    BMAGIC_WORK->unk_5C = 1;
    BMAGIC_WORK->unk_2B = 1;
    BMAGIC_WORK->unk_5D = tint;
    BMAGIC_WORK->unk_5E = tint;
    BMAGIC_WORK->unk_5F = tint;
    BMAGIC_WORK->unk_27 = g_BattleEffectBattler->unk_27;
    if ((BMAGIC_WORK->param.unk_0B & 1) == 0) {
        BMAGIC_WORK->unk_0C = 0;
        BMAGIC_WORK->unk_10 = -ONE;
    } else {
        BMAGIC_WORK->unk_0C = 0;
        BMAGIC_WORK->unk_10 = ONE;
    }
    Effect_RotatePosition(g_Task);
    BMAGIC_WORK->unk_09 = 16;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF248(void) {
    BMAGIC_WORK->pos.x.fixed += BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed += BMAGIC_WORK->unk_10;
    BMAGIC_WORK->unk_5D -= 4;
    BMAGIC_WORK->unk_5E -= 4;
    BMAGIC_WORK->unk_5F -= 4;
    if (--BMAGIC_WORK->unk_09 == 0) {
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF300(void) {
    u8 count;

    count               = BMAGIC_WORK->unk_09 + 1;
    BMAGIC_WORK->unk_09 = count;
    if ((count & BYTE_MASK) != 0x10) {
        return;
    }
    if ((BMAGIC_WORK->param.unk_0B & 1) != 0) {
        BMAGIC_WORK->unk_0C = -0x20000;
        BMAGIC_WORK->unk_10 = -0x10000;
    } else {
        BMAGIC_WORK->unk_0C = -0x20000;
        BMAGIC_WORK->unk_10 = 0x10000;
    }
    Effect_RotatePosition(g_Task);
    BMAGIC_WORK->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed + BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed + BMAGIC_WORK->unk_10;
    BMAGIC_WORK->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
    if ((BMAGIC_WORK->param.unk_0B & 1) != 0) {
        BMAGIC_WORK->unk_0C = 0;
        BMAGIC_WORK->unk_10 = 0x1000;
    } else {
        BMAGIC_WORK->unk_0C = 0;
        BMAGIC_WORK->unk_10 = -0x1000;
    }
    Effect_RotatePosition(g_Task);
    if (BMAGIC_WORK->param.unk_0B == 0) {
        SND_SEQueueSelection(0x101);
    }
    BMAGIC_WORK->unk_09 = 0x10;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF460(void) {
    PartyMember* task;
    u8           timer;

    task = g_Task;
    task->pos.x.fixed += task->unk_0C;
    task->unk_5D += 4;
    task->pos.y.fixed += task->unk_10;
    BMAGIC_WORK->unk_5E += 4;
    BMAGIC_WORK->unk_5F += 4;
    timer               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 0) {
        if (BMAGIC_WORK->param.unk_0B == 0) {
            BMAGIC_WORK->header.flags &= 0xDF;
            BMAGIC_WORK->unk_5C = 0;
            BMAGIC_WORK->unk_2B = 0;
            BMAGIC_WORK->unk_5D = 0;
            BMAGIC_WORK->unk_5E = 0;
            BMAGIC_WORK->unk_5F = 0;
            if (g_Battle.active_battler >= 3) {
                func_801E257C(g_Battle.active_battler, 2);
            }
            BMAGIC_WORK->unk_09 = func_800AFF98();
            BMAGIC_WORK->header.step += 1;
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
        counter             = BMAGIC_WORK->unk_09 - 1;
        BMAGIC_WORK->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            Battle_MarkDamaged(g_Battle.target_selector);
            Battle_PlayActiveBattlerSE(2, 4);
            BMAGIC_WORK->header.step += 1;
        }
    }
}

MATCH void func_801EF694(void) {
    if (Script_AnimStepOnce() != 0u) {
        BMAGIC_WORK->unk_09      = 8;
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
    }
}

MATCH void func_801EF6EC(void) {
    s8 tone;
    u8 timer;

    timer               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        if (g_Battle.active_battler >= 3U) {
            func_801E257C(g_Battle.active_battler, 0);
        }
        BMAGIC_WORK->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        BMAGIC_WORK->unk_5C = 1;
        BMAGIC_WORK->unk_2B = 1;
        tone                = -0x40;
        BMAGIC_WORK->unk_5D = tone;
        BMAGIC_WORK->unk_5E = tone;
        BMAGIC_WORK->unk_5F = tone;
        BMAGIC_WORK->unk_09 = 8;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF7E0(void) {
    u8 timer;

    BMAGIC_WORK->unk_5D -= 8;
    BMAGIC_WORK->unk_5E -= 8;
    BMAGIC_WORK->unk_5F -= 8;
    timer               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        BMAGIC_WORK->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        BMAGIC_WORK->unk_09      = 8;
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EF8B4(void) {
    u8 count;

    BMAGIC_WORK->unk_5D += 8;
    BMAGIC_WORK->unk_5E += 8;
    BMAGIC_WORK->unk_5F += 8;
    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF970(void) {
    Effect_Reset();
}
